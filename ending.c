//
//  ending.c
//  Hoplite Challenge
//
//  Created by Jeremy March on 3/4/17.
//  Copyright © 2017 Jeremy March. All rights reserved.
//

#include "ending.h"

#define ENDING_CAPACITY 10 //needs at least 6

void addEnding(VerbFormC *vf, UCS2 *ucs2, int *len, const int ucs2Capacity, UCS2 *ending, int elen, bool contractedFuture, bool decompose)
{
    if (decompose && contractedFuture)
    {
        if ((vf->verb->verbclass & CONTRACTED_FUTURE_ALPHA) == CONTRACTED_FUTURE_ALPHA)
            ucs2[*len] = GREEK_SMALL_LETTER_ALPHA;
        else
            ucs2[*len] = GREEK_SMALL_LETTER_EPSILON;
        ++(*len);
    }
    else if (!decompose && (vf->tense == PRESENT || vf->tense == IMPERFECT) && (utf8HasSuffix(vf->verb->present, "άω") || utf8HasSuffix(vf->verb->present, "άομαι")))
    {
        --(*len);
    }
    else if (!decompose && (vf->tense == PRESENT || vf->tense == IMPERFECT) && (utf8HasSuffix(vf->verb->present, "έω") || utf8HasSuffix(vf->verb->present, "έομαι")))
    {
        --(*len);
    }
    else if (!decompose && (vf->tense == PRESENT || vf->tense == IMPERFECT) && (utf8HasSuffix(vf->verb->present, "όω") || utf8HasSuffix(vf->verb->present, "όομαι")))
    {
        --(*len);
    }
    else if(decompose && ADD_EPSILON_TO_AORIST_PASSIVE_SUBJUNCTIVE_STEM && vf->tense == AORIST && vf->voice == PASSIVE && vf->mood == SUBJUNCTIVE)
    {
        ucsplice(ucs2, len, ucs2Capacity, *len, 0, (UCS2[]){GREEK_SMALL_LETTER_EPSILON}, 1);
    }
    /* start consonant stem perfect and pluperfect */
    else if ((vf->tense == PERFECT || vf->tense == PLUPERFECT) && (vf->voice == MIDDLE || vf->voice == PASSIVE))
    {
        //Labials: π, φ, β, μπ
        //γέγραμμαι, λέλειμαι, βέβλαμμαι, κέκλεμμαι, εἴλημμαι,  πέπεμμαι is separate
        //we check the last letter of the stem for (oraw which has two perfect middle stems, only one a consonant stem.
        if (ucs2[*len - 1] == GREEK_SMALL_LETTER_MU &&
            ((vf->verb->verbclass & CONSONANT_STEM_PERFECT_PHI) == CONSONANT_STEM_PERFECT_PHI ||
             (vf->verb->verbclass & CONSONANT_STEM_PERFECT_PI) == CONSONANT_STEM_PERFECT_PI ||
             (vf->verb->verbclass & CONSONANT_STEM_PERFECT_BETA) == CONSONANT_STEM_PERFECT_BETA))
        {
            UCS2 consonant = 0;
            if ((vf->verb->verbclass & CONSONANT_STEM_PERFECT_PHI) == CONSONANT_STEM_PERFECT_PHI)
                consonant = GREEK_SMALL_LETTER_PHI;
            else if ( (vf->verb->verbclass & CONSONANT_STEM_PERFECT_PI) == CONSONANT_STEM_PERFECT_PI)
                consonant = GREEK_SMALL_LETTER_PI;
            else if ( (vf->verb->verbclass & CONSONANT_STEM_PERFECT_BETA) == CONSONANT_STEM_PERFECT_BETA)
                consonant = GREEK_SMALL_LETTER_BETA;
            
            if (vf->person == FIRST && vf->number == SINGULAR)
            {
                if ( decompose)
                {
                    ucs2[*len - 1] = consonant;
                }
            }
            else if (vf->person == SECOND && vf->number == SINGULAR)
            {
                if ( decompose)
                {
                    ucs2[*len - 1] = consonant;
                }
                else
                {
                    ucsplice(ucs2, len, ucs2Capacity, *len -1, 1, (UCS2[]){GREEK_SMALL_LETTER_PSI}, 1);
                    ucsplice(ending, &elen, ENDING_CAPACITY, 0, 1, NULL, 0);
                }
            }
            else if (vf->person == THIRD && vf->number == SINGULAR)
            {
                if ( decompose)
                {
                    ucs2[*len - 1] = consonant;
                }
                else
                {
                    ucs2[*len - 1] = GREEK_SMALL_LETTER_PI;
                }
            }
            else if (vf->person == FIRST && vf->number == PLURAL)
            {
                if ( decompose)
                {
                    ucs2[*len - 1] = consonant;
                }
            }
            else if (vf->person == SECOND && vf->number == PLURAL)
            {
                if ( decompose)
                {
                    ucs2[*len - 1] = consonant;
                }
                else
                {
                    --(*len);
                    ending[0] = GREEK_SMALL_LETTER_PHI;
                }
            }
            else if (vf->person == THIRD && vf->number == PLURAL)
            {
                ucs2[0] = EM_DASH;
                (*len) = 1;
                return;
            }
        }
        else if ((vf->verb->verbclass & CONSONANT_STEM_PERFECT_MU_PI) == CONSONANT_STEM_PERFECT_MU_PI) //πέπεμμαι
        {
            if (vf->person == FIRST && vf->number == SINGULAR)
            {
                if ( decompose)
                {
                    ucs2[*len] = GREEK_SMALL_LETTER_PI;
                    ++(*len);
                }
            }
            else if (vf->person == SECOND && vf->number == SINGULAR)
            {
                if ( decompose)
                {
                    ucs2[*len] = GREEK_SMALL_LETTER_PI;
                    ++(*len);
                }
                else
                {
                    ending[0] = GREEK_SMALL_LETTER_PSI;
                }
            }
            else if (vf->person == THIRD && vf->number == SINGULAR)
            {
                if ( decompose)
                {
                    ucs2[*len] = GREEK_SMALL_LETTER_PI;
                    ++(*len);
                }
                else
                {
                    ucs2[*len] = GREEK_SMALL_LETTER_PI;
                    ++(*len);
                }
            }
            else if (vf->person == FIRST && vf->number == PLURAL)
            {
                if ( decompose)
                {
                    ucs2[*len] = GREEK_SMALL_LETTER_PI;
                    ++(*len);
                }
            }
            else if (vf->person == SECOND && vf->number == PLURAL)
            {
                if ( decompose)
                {
                    ucs2[*len] = GREEK_SMALL_LETTER_PI;
                    ++(*len);
                }
                else
                {
                    ending[0] = GREEK_SMALL_LETTER_PHI;
                }
            }
            else if (vf->person == THIRD && vf->number == PLURAL)
            {
                ucs2[0] = EM_DASH;
                (*len) = 1;
                return;
            }
        }
        //Stops: γ, χ, κ
        else if (ucs2[*len - 1] == GREEK_SMALL_LETTER_GAMMA &&
                 ((vf->verb->verbclass & CONSONANT_STEM_PERFECT_KAPPA) == CONSONANT_STEM_PERFECT_KAPPA ||
                  (vf->verb->verbclass & CONSONANT_STEM_PERFECT_CHI) == CONSONANT_STEM_PERFECT_CHI ||
                  (vf->verb->verbclass & CONSONANT_STEM_PERFECT_GAMMA) == CONSONANT_STEM_PERFECT_GAMMA))
        {
            UCS2 consonant = 0;
            if ((vf->verb->verbclass & CONSONANT_STEM_PERFECT_KAPPA) == CONSONANT_STEM_PERFECT_KAPPA)
                consonant = GREEK_SMALL_LETTER_KAPPA;
            else if ( (vf->verb->verbclass & CONSONANT_STEM_PERFECT_CHI) == CONSONANT_STEM_PERFECT_CHI)
                consonant = GREEK_SMALL_LETTER_CHI;
            else if ( (vf->verb->verbclass & CONSONANT_STEM_PERFECT_GAMMA) == CONSONANT_STEM_PERFECT_GAMMA)
                consonant = GREEK_SMALL_LETTER_GAMMA;
            
            if (vf->person == FIRST && vf->number == SINGULAR)
            {
                if ( decompose)
                {
                    ucs2[*len - 1] = consonant;
                }
            }
            else if (vf->person == SECOND && vf->number == SINGULAR)
            {
                if ( decompose)
                {
                    ucs2[*len - 1] = consonant;
                }
                else
                {
                    --(*len);
                    ending[0] = GREEK_SMALL_LETTER_XI;
                }
            }
            else if (vf->person == THIRD && vf->number == SINGULAR)
            {
                if ( decompose)
                {
                    ucs2[*len - 1] = consonant;
                }
                else
                {
                    ucs2[*len - 1] = GREEK_SMALL_LETTER_KAPPA;
                }
            }
            else if (vf->person == FIRST && vf->number == PLURAL)
            {
                if ( decompose)
                {
                    ucs2[*len - 1] = consonant;
                }
            }
            else if (vf->person == SECOND && vf->number == PLURAL)
            {
                if ( decompose)
                {
                    ucs2[*len - 1] = consonant;
                }
                else
                {
                    --(*len);
                    ending[0] = GREEK_SMALL_LETTER_CHI;
                }
            }
            else if (vf->person == THIRD && vf->number == PLURAL)
            {
                ucs2[0] = EM_DASH;
                (*len) = 1;
                return;
            }
        }
        else if ((vf->verb->verbclass & CONSONANT_STEM_PERFECT_SIGMA) == CONSONANT_STEM_PERFECT_SIGMA ||
                 ((vf->verb->verbclass & CONSONANT_STEM_PERFECT_SIGMA_2) == CONSONANT_STEM_PERFECT_SIGMA_2 &&
                  ucs2[(*len)-1] == GREEK_SMALL_LETTER_SIGMA)) //κεκέλευσμαι or σῴζω which is both consonant stem and not.
        {
            if (vf->person == SECOND && vf->number == SINGULAR)
            {
                if (!decompose)
                {
                    ucsplice(ending, &elen, ENDING_CAPACITY, 0, 1, NULL, 0);
                }
            }
            else if (vf->person == SECOND && vf->number == PLURAL)
            {
                if (!decompose)
                {
                    ucsplice(ending, &elen, ENDING_CAPACITY, 0, 1, NULL, 0);
                }
            }
            else if (vf->person == THIRD && vf->number == PLURAL)
            {
                ucs2[0] = EM_DASH;
                (*len) = 1;
                return;
            }
        }
        else if ((vf->verb->verbclass & CONSONANT_STEM_PERFECT_LAMBDA) == CONSONANT_STEM_PERFECT_LAMBDA) //ἄγγελμαι
        {
            //H&Q page 273, only different in 2nd and 3rd person plural
            if (vf->person == SECOND && vf->number == PLURAL)
            {
                if (!decompose)
                {
                    ucsplice(ending, &elen, ENDING_CAPACITY, 0, 1, NULL, 0);
                }
            }
            else if (vf->person == THIRD && vf->number == PLURAL)
            {
                ucs2[0] = EM_DASH;
                (*len) = 1;
                return;
            }
        }
        else if ((vf->verb->verbclass & CONSONANT_STEM_PERFECT_NU) == CONSONANT_STEM_PERFECT_NU) //αισχυνομαι
        {
            if (vf->person == FIRST && vf->number == SINGULAR)
            {
                if ( decompose)
                {
                    ucs2[*len - 1] = GREEK_SMALL_LETTER_NU;
                }
            }
            else if (vf->person == SECOND && vf->number == SINGULAR)
            {
                ucs2[0] = EM_DASH;
                *len = 1;
                elen = 0;
                return;
            }
            else if (vf->person == THIRD && vf->number == SINGULAR)
            {
                if ( decompose)
                {
                    ucs2[*len - 1] = GREEK_SMALL_LETTER_NU;
                }
                else
                {
                    ucs2[*len - 1] = GREEK_SMALL_LETTER_NU;
                }
            }
            else if (vf->person == FIRST && vf->number == PLURAL)
            {
                if ( decompose)
                {
                    ucs2[*len - 1] = GREEK_SMALL_LETTER_NU;
                }
            }
            else if (vf->person == SECOND && vf->number == PLURAL)
            {
                ucs2[*len - 1] = GREEK_SMALL_LETTER_NU;
                
                if (!decompose)
                {
                    ucsplice(ending, &elen, ENDING_CAPACITY, 0, 1, NULL, 0);
                }
            }
            else if (vf->person == THIRD && vf->number == PLURAL)
            {
                ucs2[0] = EM_DASH;
                (*len) = 1;
                return;
            }
        }
    }
    else if (vf->tense == FUTURE && vf->voice == PASSIVE) //add future passive infix hs here
    {
        if (decompose)
        {
            ucsplice(ucs2, len, ucs2Capacity, *len, 0, (UCS2[]){SPACE,HYPHEN,SPACE}, 3);
        }
        ucsplice(ucs2, len, ucs2Capacity, *len, 0, (UCS2[]){GREEK_SMALL_LETTER_ETA,GREEK_SMALL_LETTER_SIGMA}, 2);
    }
    /* start mi verbs present tense */
    else if (vf->tense == PRESENT &&
             (utf8HasSuffix(vf->verb->present, "μι") ||
              utf8HasSuffix(vf->verb->present, "φημί") ||
              utf8HasSuffix(vf->verb->present, "αμαι") ||
              utf8HasSuffix(vf->verb->present, "νυμαι"))) //mi verbs, present tense
    {
        if (vf->voice != ACTIVE || vf->number == PLURAL || vf->mood == OPTATIVE || vf->mood == IMPERATIVE || vf->mood == SUBJUNCTIVE)
        {
            if (ucs2[*len - 1] == GREEK_SMALL_LETTER_OMEGA)
                ucsplice(ucs2, len, ucs2Capacity, *len - 1, 1, (UCS2[]){GREEK_SMALL_LETTER_OMICRON}, 1);
            else if (ucs2[*len - 1] == GREEK_SMALL_LETTER_ETA && (ucs2[*len - 2] == GREEK_SMALL_LETTER_TAU || ucs2[*len - 2] == GREEK_SMALL_LETTER_PHI))
                ucsplice(ucs2, len, ucs2Capacity, *len - 1, 1, (UCS2[]){GREEK_SMALL_LETTER_ALPHA}, 1);
            else if (ucs2[*len - 1] == GREEK_SMALL_LETTER_ETA)
                ucsplice(ucs2, len, ucs2Capacity, *len - 1, 1, (UCS2[]){GREEK_SMALL_LETTER_EPSILON}, 1);
            else if (ucs2[*len - 1] == COMBINING_MACRON) //deiknumi
                ucsplice(ucs2, len, ucs2Capacity, *len - 1, 1, NULL, 0); //remove one (macron) --(*len);
        }
        //contract third plural indicative of isthmi
        if (vf->person == THIRD && vf->number == PLURAL && vf->mood == INDICATIVE && vf->voice == ACTIVE && (utf8HasSuffix(vf->verb->present, "στημι") || utf8HasSuffix(vf->verb->present, "ῑ̔́ημι") || utf8HasSuffix(vf->verb->present, "ῑ́ημι")))
        {
            if (!decompose)
            {
                ucsplice(ucs2, len, ucs2Capacity, *len - 1, 1, NULL, 0);
                ucsplice(ending, &elen, ENDING_CAPACITY, 0, 2, (UCS2[]){GREEK_SMALL_LETTER_ALPHA_WITH_PERISPOMENI}, 1);
            }
        }
        else if (vf->person == THIRD && vf->number == PLURAL && vf->mood == INDICATIVE && vf->voice == ACTIVE && utf8HasSuffix(vf->verb->present, "φημί"))
        {
            if (!decompose)
            {
                ucsplice(ucs2, len, ucs2Capacity, *len - 1, 1, NULL, 0); //--(*len);
            }
        }
        else if (vf->person == SECOND && vf->number == SINGULAR && vf->mood == INDICATIVE && vf->voice == ACTIVE &&
                 (utf8HasSuffix(vf->verb->present, "ῑ̔́ημι") ||
                  utf8HasSuffix(vf->verb->present, "ῑ́ημι")) &&
                 ending[0] == GREEK_SMALL_LETTER_EPSILON)
        {
            //alt ending for ihmi
            if (!decompose)
                --(*len);
            else
                ucs2[*len - 1] = GREEK_SMALL_LETTER_EPSILON;
        }
        else if (vf->person == SECOND && vf->number == SINGULAR && vf->mood == INDICATIVE && vf->voice == ACTIVE &&
                 utf8HasSuffix(vf->verb->present, "φημί") )
        {
            //alt ending for fhmi
            ucsplice(ucs2, len, ucs2Capacity, 1, 1, (UCS2[]){GREEK_SMALL_LETTER_ETA_WITH_YPOGEGRAMMENI}, 1);
        }
        else if (utf8HasSuffix(vf->verb->present, "εἶμι"))
        {
            if (vf->person == SECOND && vf->number == SINGULAR && vf->mood == INDICATIVE)
            {
                ucsplice(ucs2, len, ucs2Capacity, 1, 1, (UCS2[]){GREEK_SMALL_LETTER_IOTA_WITH_PSILI_AND_PERISPOMENI}, 1);
                elen = 0;
            }
            else if (vf->number == PLURAL && vf->mood == INDICATIVE)
            {
                ucsplice(ucs2, len, ucs2Capacity, 0, 1, NULL, 0);
            }
        }
        
        if (vf->mood == SUBJUNCTIVE)
        {
            if (!decompose && !utf8HasSuffix(vf->verb->present, "ῡμι") && !utf8HasSuffix(vf->verb->present, "νυμαι"))
            {
                --(*len);
            }
            if ( utf8HasSuffix(vf->verb->present, "δίδωμι"))
            {
                if (!decompose)
                {
                    if ( vf->person == SECOND && vf->number == SINGULAR)
                        ending[0] = GREEK_SMALL_LETTER_OMEGA_WITH_PERISPOMENI_AND_YPOGEGRAMMENI;
                    else if ( vf->person == THIRD && vf->number == SINGULAR && vf->voice == ACTIVE)
                        ending[0] = GREEK_SMALL_LETTER_OMEGA_WITH_PERISPOMENI_AND_YPOGEGRAMMENI;
                    else if ( vf->person == THIRD && vf->number == SINGULAR && vf->voice != ACTIVE)
                        ending[0] = GREEK_SMALL_LETTER_OMEGA_WITH_PERISPOMENI;
                    else if ( vf->person == SECOND && vf->number == PLURAL)
                        ending[0] = GREEK_SMALL_LETTER_OMEGA_WITH_PERISPOMENI;
                }
            }
            else if (utf8HasSuffix(vf->verb->present, "εἶμι"))
            {
                if (decompose)
                {
                    --(*len);
                }
                ucs2[0] = GREEK_SMALL_LETTER_IOTA_WITH_PSILI;
            }
            if ((utf8HasSuffix(vf->verb->present, "ἐπίσταμαι") || utf8HasSuffix(vf->verb->present, "δύναμαι")) && decompose)
            {
                ucsplice(ucs2, len, ucs2Capacity, *len - 1, 1, NULL, 0);
            }
            else if (( utf8HasSuffix(vf->verb->present, "στημι") || utf8HasSuffix(vf->verb->present, "αμαι") || utf8HasSuffix(vf->verb->present, "φημί")) && decompose)
            {
                ucs2[*len - 1] = GREEK_SMALL_LETTER_EPSILON;
            }
        }
        if (vf->mood == OPTATIVE && !utf8HasSuffix(vf->verb->present, "ῡμι") && !utf8HasSuffix(vf->verb->present, "νυμαι"))
        {
            //exceptional alternates H&Q page 347
            if (vf->tense == PRESENT && vf->mood == OPTATIVE && vf->voice != ACTIVE && utf8HasSuffix(vf->verb->present, "τίθημι") && (vf->number == PLURAL || vf->person == THIRD))
            {
                if (ending[0] == GREEK_SMALL_LETTER_OMICRON && !decompose)// this is right
                    --(*len);
                else if (ending[0] == GREEK_SMALL_LETTER_EPSILON)
                    ucsplice(ending, &elen, ENDING_CAPACITY, 0, 1, NULL, 0);
            }
            else if (utf8HasSuffix(vf->verb->present, "εἶμι"))
            {
                ucs2[0] = GREEK_SMALL_LETTER_IOTA_WITH_PSILI;
                *len = 1;
            }
            else
            {
                ucsplice(ending, &elen, ENDING_CAPACITY, 0, 1, NULL, 0);
                //h&q p 504
                if (vf->person != FIRST && vf->voice != ACTIVE && !utf8HasSuffix(vf->verb->present, "ἐπίσταμαι") && !utf8HasSuffix(vf->verb->present, "δύναμαι")) //H&Q page 503, 607 and 676
                {
                    ending[0] = GREEK_SMALL_LETTER_IOTA_WITH_PERISPOMENI;
                }
            }
        }
        if (vf->mood == IMPERATIVE)
        {
            if (utf8HasSuffix(vf->verb->present, "εἶμι"))
            {
                if (vf->person == SECOND && vf->number == SINGULAR)
                {
                    ucs2[0] = GREEK_SMALL_LETTER_IOTA_WITH_PSILI;
                    *len = 1;
                    ending[0] = GREEK_SMALL_LETTER_THETA;
                    ending[1] = GREEK_SMALL_LETTER_IOTA;
                    elen = 2;
                }
                else if (vf->person == SECOND && vf->number == PLURAL)
                {
                    ucs2[0] = GREEK_SMALL_LETTER_IOTA_WITH_PSILI;
                    *len = 1;
                    ucsplice(ending, &elen, ENDING_CAPACITY, 0, 1, NULL, 0);
                }
                else if (vf->person == THIRD && vf->number == SINGULAR)
                {
                    ucs2[0] = GREEK_SMALL_LETTER_IOTA_WITH_PSILI;
                    *len = 1;
                    ucsplice(ending, &elen, ENDING_CAPACITY, 0, 1, NULL, 0);
                }
                else if (vf->person == THIRD && vf->number == PLURAL)
                {
                    ucs2[0] = GREEK_SMALL_LETTER_IOTA_WITH_PSILI;
                    *len = 1;
                }
            }
            else if (vf->person == SECOND && vf->number == SINGULAR)
            {
                if ( utf8HasSuffix(vf->verb->present, "δίδωμι"))
                {
                    if (vf->voice == ACTIVE)
                    {
                        if (!decompose)
                        {
                            ending[0] = GREEK_SMALL_LETTER_UPSILON;
                        }
                    }
                    else
                    {
                        ending[0] = GREEK_SMALL_LETTER_SIGMA;
                        ending[1] = GREEK_SMALL_LETTER_OMICRON;
                    }
                }
                else if ( ( utf8HasSuffix(vf->verb->present, "στημι") || utf8HasSuffix(vf->verb->present, "αμαι")))
                {
                    if (vf->voice == ACTIVE)
                    {
                        if (!decompose)
                        {
                            --(*len);
                            ending[0] = GREEK_SMALL_LETTER_ETA;
                        }
                    }
                    else
                    {
                        ending[0] = GREEK_SMALL_LETTER_SIGMA;
                        ending[1] = GREEK_SMALL_LETTER_OMICRON;
                    }
                }
                else if ( utf8HasSuffix(vf->verb->present, "τίθημι") || utf8HasSuffix(vf->verb->present, "ῑ̔́ημι") || utf8HasSuffix(vf->verb->present, "ῑ́ημι"))
                {
                    if (vf->voice == ACTIVE)
                    {
                        if (!decompose)
                        {
                            ending[0] = GREEK_SMALL_LETTER_IOTA;
                        }
                    }
                    else
                    {
                        ending[0] = GREEK_SMALL_LETTER_SIGMA;
                        ending[1] = GREEK_SMALL_LETTER_OMICRON;
                    }
                }
                else if ( utf8HasSuffix(vf->verb->present, "ῡμι") || utf8HasSuffix(vf->verb->present, "νυμαι"))
                {
                    if (vf->voice == ACTIVE)
                    {
                        elen = 0;
                        ++(*len);
                        ucs2[*len - 1] = COMBINING_MACRON;
                    }
                    else
                    {
                        ending[0] = GREEK_SMALL_LETTER_SIGMA;
                        ending[1] = GREEK_SMALL_LETTER_OMICRON;
                    }
                }
                else if (utf8HasSuffix(vf->verb->present, "φημί"))
                {
                    ending[0] = GREEK_SMALL_LETTER_THETA;
                    ending[1] = GREEK_SMALL_LETTER_IOTA;
                    elen = 2;
                }
            }
            else
            {
                ucsplice(ending, &elen, ENDING_CAPACITY, 0, 1, NULL, 0);
            }
        }
    }
    else if (vf->tense == IMPERFECT &&
             (utf8HasSuffix(vf->verb->present, "μι") ||
              utf8HasSuffix(vf->verb->present, "αμαι") ||
              utf8HasSuffix(vf->verb->present, "φημί") ||
              utf8HasSuffix(vf->verb->present, "νυμαι"))) //mi verbs
    {
        if (utf8HasSuffix(vf->verb->present, "εἶμι"))
        {
            if (vf->person == FIRST && vf->number == SINGULAR)
            {
                if (elen < 3)
                {
                    ending[0] = GREEK_SMALL_LETTER_ALPHA;
                    elen = 1;
                }
            }
            else if (vf->person == SECOND && vf->number == SINGULAR)
            {
                if (elen < 3) //hehe
                {
                    ending[0] = GREEK_SMALL_LETTER_EPSILON;
                    ending[1] = GREEK_SMALL_LETTER_IOTA;
                    ending[2] = GREEK_SMALL_LETTER_SIGMA;
                    ending[3] = GREEK_SMALL_LETTER_THETA;
                    ending[4] = GREEK_SMALL_LETTER_ALPHA;
                    elen = 5;
                }
                else
                {
                    ending[0] = GREEK_SMALL_LETTER_EPSILON; //this fixes the overwritting, see the other //hehe
                }
            }
            else if (vf->person == THIRD && vf->number == SINGULAR)
            {
                ucsplice(ending, &elen, ENDING_CAPACITY, 1, 0, (UCS2[]){GREEK_SMALL_LETTER_IOTA}, 1);
            }
            else if (vf->person == FIRST && vf->number == PLURAL)
            {
                ucsplice(ending, &elen, ENDING_CAPACITY, 0, 1, NULL, 0);
            }
            else if (vf->person == SECOND && vf->number == PLURAL)
            {
                ucsplice(ending, &elen, ENDING_CAPACITY, 0, 1, NULL, 0);
            }
            else if (vf->person == THIRD && vf->number == PLURAL)
            {
                if (elen < 3)
                {
                    ucsplice(ending, &elen, ENDING_CAPACITY, 0, 1, (UCS2[]){GREEK_SMALL_LETTER_SIGMA,GREEK_SMALL_LETTER_ALPHA}, 2);
                }
            }
        }
        else if ( utf8HasSuffix(vf->verb->present, "δίδωμι") && vf->voice == ACTIVE)
        {
            //H&Q page 342
            //shorten stem vowel
            if (ucs2[*len - 1] == GREEK_SMALL_LETTER_OMEGA)
            {
                ucs2[*len - 1] = GREEK_SMALL_LETTER_OMICRON;
            }
            
            if ( vf->number == SINGULAR && vf->voice == ACTIVE)
            {
                if (!decompose)
                {
                    ++(*len);
                    ucs2[*len - 1] = GREEK_SMALL_LETTER_UPSILON;
                }
                if (vf->person == FIRST || vf->person == SECOND)
                {
                    if (!decompose)
                    {
                        ucsplice(ending, &elen, ENDING_CAPACITY, 0, 1, NULL, 0);
                    }
                }
                else if (vf->person == THIRD)
                {
                    if (!decompose)
                    {
                        elen = 0;
                    }
                    else
                    {
                        elen = 1;
                        ending[0] = GREEK_SMALL_LETTER_EPSILON;
                    }
                }
            }
            else if (vf->number == PLURAL && vf->voice == ACTIVE)
            {
                ucsplice(ending, &elen, ENDING_CAPACITY, 0, 1, NULL, 0);
                if (vf->person == THIRD)
                {
                    ending[0] = GREEK_SMALL_LETTER_SIGMA;
                    ending[1] = GREEK_SMALL_LETTER_ALPHA;
                    ending[2] = GREEK_SMALL_LETTER_NU;
                    elen += 2;
                }
            }
        }
        else if ( utf8HasSuffix(vf->verb->present, "στημι") && vf->voice == ACTIVE)
        {
            //shorten stem vowel
            if (vf->number == PLURAL)
                ucs2[*len - 1] = GREEK_SMALL_LETTER_ALPHA;
            
            ucsplice(ending, &elen, ENDING_CAPACITY, 0, 1, NULL, 0);
            if (vf->person == THIRD && vf->number == SINGULAR)
            {
                elen -= 3;
            }
            if (vf->person == THIRD && vf->number == PLURAL)
            {
                ending[0] = GREEK_SMALL_LETTER_SIGMA;
                ending[1] = GREEK_SMALL_LETTER_ALPHA;
                ending[2] = GREEK_SMALL_LETTER_NU;
                elen += 2;
            }
        }
        else if ( utf8HasSuffix(vf->verb->present, "φημί") && vf->voice == ACTIVE)
        {
            //shorten stem vowel
            if (vf->number == PLURAL)
                ucs2[*len - 1] = GREEK_SMALL_LETTER_ALPHA;
            
            ucsplice(ending, &elen, ENDING_CAPACITY, 0, 1, NULL, 0);
            if (vf->person == THIRD && vf->number == SINGULAR)
            {
                elen -= 3;
            }
            if (vf->person == THIRD && vf->number == PLURAL)
            {
                ending[0] = GREEK_SMALL_LETTER_SIGMA;
                ending[1] = GREEK_SMALL_LETTER_ALPHA;
                ending[2] = GREEK_SMALL_LETTER_NU;
                elen += 2;
            }
        }
        else if ( (utf8HasSuffix(vf->verb->present, "τίθημι") ||
                   utf8HasSuffix(vf->verb->present, "ῑ̔́ημι") ||
                   utf8HasSuffix(vf->verb->present, "ῑ́ημι")) && vf->voice == ACTIVE)
        {
            if (vf->person != FIRST || vf->number == PLURAL)
                ucs2[*len - 1] = GREEK_SMALL_LETTER_EPSILON;
            
            if (vf->person == THIRD && vf->number == PLURAL)
            {
                ucsplice(ending, &elen, ENDING_CAPACITY, 0, 1, NULL, 0);
                ending[0] = GREEK_SMALL_LETTER_SIGMA;
                ending[1] = GREEK_SMALL_LETTER_ALPHA;
                ending[2] = GREEK_SMALL_LETTER_NU;
                elen += 2;
            }
            else if (vf->person == FIRST || vf->number == PLURAL)
            {
                ucsplice(ending, &elen, ENDING_CAPACITY, 0, 1, NULL, 0);
            }
            else if (vf->person == SECOND && vf->number == SINGULAR)
            {
                if (!decompose)
                {
                    ++(*len);
                    ucs2[*len - 1] = GREEK_SMALL_LETTER_IOTA;
                    ending[0] = GREEK_SMALL_LETTER_FINAL_SIGMA;
                    elen = 1;
                }
                else
                {
                    //H&Q page 342, 520
                    ending[0] = GREEK_SMALL_LETTER_EPSILON;
                    ending[1] = GREEK_SMALL_LETTER_FINAL_SIGMA;
                    elen = 2;
                }
            }
            else if (vf->person == THIRD && vf->number == SINGULAR)
            {
                if (!decompose)
                {
                    ++(*len);
                    ucs2[*len - 1] = GREEK_SMALL_LETTER_IOTA;
                    elen = 0;
                }
                else
                {
                    //H&Q page 342, 520
                    ending[0] = GREEK_SMALL_LETTER_EPSILON;
                    elen = 1;
                }
            }
        }
        else if ( utf8HasSuffix(vf->verb->present, "ῡμι") && vf->voice == ACTIVE)
        {
            if (vf->number == PLURAL)
            {
                if (ucs2[*len - 1] == COMBINING_MACRON) //deiknumi
                    --(*len);
            }
            
            if (vf->person == THIRD && vf->number == PLURAL)
            {
                ucsplice(ending, &elen, ENDING_CAPACITY, 0, 1, (UCS2[]){GREEK_SMALL_LETTER_SIGMA,GREEK_SMALL_LETTER_ALPHA}, 2);
            }
            else if (vf->person == FIRST || vf->number == PLURAL)
            {
                ucsplice(ending, &elen, ENDING_CAPACITY, 0, 1, NULL, 0);
            }
            else if (vf->person == SECOND && vf->number == SINGULAR)
            {
                ending[0] = GREEK_SMALL_LETTER_FINAL_SIGMA;
                elen = 1;
            }
            else if (vf->person == THIRD && vf->number == SINGULAR)
            {
                elen = 0;
            }
        }
        else if (vf->voice != ACTIVE)
        {
            //shorten stem vowel
            if (ucs2[*len - 1] == GREEK_SMALL_LETTER_OMEGA)
                ucs2[*len - 1] = GREEK_SMALL_LETTER_OMICRON;
            else if (ucs2[*len - 1] == GREEK_SMALL_LETTER_ETA && ucs2[*len - 2] == GREEK_SMALL_LETTER_TAU )
                ucs2[*len - 1] = GREEK_SMALL_LETTER_ALPHA;
            else if (ucs2[*len - 1] == GREEK_SMALL_LETTER_ETA )
                ucs2[*len - 1] = GREEK_SMALL_LETTER_EPSILON;
            else if (ucs2[*len - 1] == COMBINING_MACRON) //deiknumi
                --(*len);
            
            ucsplice(ending, &elen, ENDING_CAPACITY, 0, 1, NULL, 0);
            if (vf->person == SECOND && vf->number == SINGULAR)
            {
                if (utf8HasSuffix(vf->verb->present, "δύναμαι") || utf8HasSuffix(vf->verb->present, "ἐπίσταμαι") )
                {   //h&q page 503, 504
                    if (!decompose)
                    {
                        --(*len);
                        ending[0] = GREEK_SMALL_LETTER_OMEGA;
                        elen = 1;
                    }
                    else
                    {
                        ending[0] = GREEK_SMALL_LETTER_OMICRON;
                        elen = 1;
                    }
                }
                else
                {
                    ending[0] = GREEK_SMALL_LETTER_SIGMA;
                    ending[1] = GREEK_SMALL_LETTER_OMICRON;
                    elen = 2;
                }
            }
        }
    }
    /* start mi verbs aorist tense */
    else if (vf->tense == AORIST &&
             (utf8HasSuffix(vf->verb->present, "μι")  ||
              utf8HasSuffix(vf->verb->present, "σταμαι")) &&
             !utf8HasSuffix(vf->verb->present, "ῡμι")) //mi verbs
    {
        if (vf->voice == ACTIVE)
        {
            if (vf->mood == SUBJUNCTIVE)
            {
                if ( utf8HasSuffix(vf->verb->present, "τίθημι"))
                {
                    if (decompose)
                    {
                        (*len) -= 1;
                        ucs2[(*len) - 1] = GREEK_SMALL_LETTER_EPSILON;
                    }
                    else
                    {
                        (*len) -= 2;
                    }
                }
                else if ( utf8HasSuffix(vf->verb->present, "ῑ́ημι"))
                {
                    if (decompose)
                    {
                        //(*len) -= 1;
                        ucs2[(*len) - 2] = SPACE;
                        ucs2[(*len) - 1] = GREEK_SMALL_LETTER_EPSILON_WITH_DASIA;
                    }
                    else
                    {
                        (*len) -= 2;
                    }
                }
                else if ( utf8HasSuffix(vf->verb->present, "ῑ̔́ημι"))
                {
                    if (decompose)
                    {
                        (*len) -= 1;
                        ucs2[(*len) - 1] = GREEK_SMALL_LETTER_EPSILON_WITH_DASIA;
                    }
                    else
                    {
                        (*len) -= 2;
                        if (vf->person == FIRST)
                        {
                            if (vf->number == SINGULAR)
                                ending[0] = GREEK_SMALL_LETTER_OMEGA_WITH_DASIA_AND_PERISPOMENI;
                            else
                                ending[0] = GREEK_SMALL_LETTER_OMEGA_WITH_DASIA_AND_PERISPOMENI;
                        }
                        else if (vf->person == SECOND)
                        {
                            if (vf->number == SINGULAR)
                                ending[0] = GREEK_SMALL_LETTER_ETA_WITH_DASIA_AND_PERISPOMENI_AND_YPOGEGRAMMENI;
                            else
                                ending[0] = GREEK_SMALL_LETTER_ETA_WITH_DASIA_AND_PERISPOMENI;
                        }
                        else if (vf->person == THIRD)
                        {
                            if (vf->number == SINGULAR)
                                ending[0] = GREEK_SMALL_LETTER_ETA_WITH_DASIA_AND_PERISPOMENI_AND_YPOGEGRAMMENI;
                            else
                                ending[0] = GREEK_SMALL_LETTER_OMEGA_WITH_DASIA_AND_PERISPOMENI;
                        }
                    }
                }
                else if ( utf8HasSuffix(vf->verb->present, "δίδωμι") )
                {
                    if (decompose)
                    {
                        (*len) -= 1;
                        ucs2[(*len) - 1] = GREEK_SMALL_LETTER_OMICRON;
                    }
                    else
                    {
                        (*len) -= 2;
                    }
                    if (!decompose)
                    {
                        if ((vf->person == SECOND || vf->person == THIRD) && vf->number == SINGULAR)
                        {
                            ending[0] = GREEK_SMALL_LETTER_OMEGA_WITH_PERISPOMENI_AND_YPOGEGRAMMENI;
                        }
                        else if (vf->person == SECOND && vf->number == PLURAL)
                        {
                            ending[0] = GREEK_SMALL_LETTER_OMEGA_WITH_PERISPOMENI;
                        }
                    }
                }
                else if ((utf8HasSuffix(vf->verb->present, "στημι") || utf8HasSuffix(vf->verb->present, "σταμαι")) && ucs2[*len -1] == GREEK_SMALL_LETTER_ETA)
                {
                    //root aorist
                    if (decompose)
                    {
                        ucs2[(*len) - 1] = GREEK_SMALL_LETTER_EPSILON; //yes epsilon
                    }
                    else
                    {
                        (*len) -= 1;
                    }
                }
            }
            else if (vf->mood == OPTATIVE)
            {
                if ( utf8HasSuffix(vf->verb->present, "τίθημι") || utf8HasSuffix(vf->verb->present, "δίδωμι") )
                {
                    (*len) -= 1;
                    if (ucs2[*len - 1] == GREEK_SMALL_LETTER_OMEGA)
                        ucs2[*len - 1] = GREEK_SMALL_LETTER_OMICRON;
                    else if (ucs2[*len - 1] == GREEK_SMALL_LETTER_ETA )
                        ucs2[*len - 1] = GREEK_SMALL_LETTER_EPSILON;
                    ucsplice(ending, &elen, ENDING_CAPACITY, 0, 1, NULL, 0);
                }
                else if ( utf8HasSuffix(vf->verb->present, "ῑ̔́ημι") )
                {
                    if (decompose)
                    {
                        *len = 2;
                        //ucs2[0] = HYPHEN;
                        ucs2[1] = GREEK_SMALL_LETTER_EPSILON_WITH_DASIA;
                        ucsplice(ending, &elen, ENDING_CAPACITY, 0, 1, NULL, 0);
                    }
                    else
                    {
                        (*len) -= 2;
                        ending[1] = GREEK_SMALL_LETTER_IOTA_WITH_DASIA;
                    }
                }
                else if ( utf8HasSuffix(vf->verb->present, "ῑ́ημι") )
                {
                    if (!decompose)
                    {
                        (*len) -= 2;
                    }
                    else
                    {
                        (*len) -= 1;
                        ucs2[*len - 1] = GREEK_SMALL_LETTER_EPSILON_WITH_DASIA;
                        ucsplice(ending, &elen, ENDING_CAPACITY, 0, 1, NULL, 0);
                    }
                }
                else if ((utf8HasSuffix(vf->verb->present, "στημι") || utf8HasSuffix(vf->verb->present, "σταμαι")) && ucs2[*len -1] == GREEK_SMALL_LETTER_ETA)
                {
                    //root aorist
                    ucs2[*len - 1] = GREEK_SMALL_LETTER_ALPHA;
                    ucsplice(ending, &elen, ENDING_CAPACITY, 0, 1, NULL, 0);
                }
            }
            else if (vf->mood == IMPERATIVE)
            {
                if ( utf8HasSuffix(vf->verb->present, "τίθημι") )
                {
                    (*len) -= 1;
                    ucs2[*len - 1] = GREEK_SMALL_LETTER_EPSILON;
                }
                else if ( utf8HasSuffix(vf->verb->present, "δίδωμι") )
                {
                    (*len) -= 1;
                    ucs2[*len - 1] = GREEK_SMALL_LETTER_OMICRON;
                }
                else if ( (utf8HasSuffix(vf->verb->present, "στημι") || utf8HasSuffix(vf->verb->present, "σταμαι")) && ucs2[*len -1] == GREEK_SMALL_LETTER_ETA )
                {
                    //root aorist
                    if (vf->person == THIRD && vf->number == PLURAL)
                        ucs2[*len - 1] = GREEK_SMALL_LETTER_ALPHA;
                }
                else if ( utf8HasSuffix(vf->verb->present, "ῑ́ημι"))
                {
                    if (!decompose)
                        ucsplice(ucs2, len, ucs2Capacity, *len - 2, 2, (UCS2[]){GREEK_SMALL_LETTER_EPSILON}, 1);
                    else
                        ucsplice(ucs2, len, ucs2Capacity, *len - 2, 2, (UCS2[]){GREEK_SMALL_LETTER_EPSILON_WITH_DASIA}, 1);
                    if (0)///vf->person == SECOND && vf->number == SINGULAR)
                    {
                        ucs2[*len - 1] = GREEK_SMALL_LETTER_FINAL_SIGMA;
                    }
                }
                else if ( utf8HasSuffix(vf->verb->present, "ῑ̔́ημι"))
                {
                    ucsplice(ucs2, len, ucs2Capacity, 1, 2, (UCS2[]){GREEK_SMALL_LETTER_EPSILON_WITH_DASIA}, 1);
                }
            }
            else if ( utf8HasSuffix(vf->verb->present, "τίθημι") || utf8HasSuffix(vf->verb->present, "δίδωμι"))
            {
                if (vf->number == PLURAL && vf->voice == ACTIVE && vf->mood == INDICATIVE)
                {
                    --(*len);
                    if (ucs2[*len - 1] == GREEK_SMALL_LETTER_OMEGA)
                        ucs2[*len - 1] = GREEK_SMALL_LETTER_OMICRON;
                    else if (ucs2[*len - 1] == GREEK_SMALL_LETTER_ETA )
                        ucs2[*len - 1] = GREEK_SMALL_LETTER_EPSILON;
                    
                    if (vf->person == THIRD)
                    {
                        ucsplice(ending, &elen, ENDING_CAPACITY, 0, 0, (UCS2[]){GREEK_SMALL_LETTER_SIGMA}, 1);
                    }
                    else
                    {
                        ucsplice(ending, &elen, ENDING_CAPACITY, 0, 1, NULL, 0);
                    }
                }
            }
            else if ( utf8HasSuffix(vf->verb->present, "ῑ̔́ημι") || utf8HasSuffix(vf->verb->present, "ῑ́ημι"))
            {
                if (vf->number == PLURAL && vf->voice == ACTIVE && vf->mood == INDICATIVE)
                {
                    ucsplice(ucs2, len, ucs2Capacity/*fix me*/, *len-2, 1, (UCS2[]){GREEK_SMALL_LETTER_EPSILON}, 1);
                    
                    if (utf8HasSuffix(vf->verb->present, "ῑ̔́ημι"))
                        ucs2[(*len) - 1] = GREEK_SMALL_LETTER_IOTA_WITH_DASIA;
                    else
                        ucs2[(*len) - 1] = GREEK_SMALL_LETTER_IOTA;
                    
                    if (decompose)
                    {
                        ucsplice(ucs2, len, ucs2Capacity, *len - 2, 2, (UCS2[]){GREEK_SMALL_LETTER_EPSILON_WITH_DASIA}, 1);
                    }
                    
                    if (vf->person == THIRD)
                    {
                        ucsplice(ending, &elen, ENDING_CAPACITY, 0, 0, (UCS2[]){GREEK_SMALL_LETTER_SIGMA}, 1);
                    }
                    else
                    {
                        ucsplice(ending, &elen, ENDING_CAPACITY, 0, 1, NULL, 0);
                    }
                }
                else if (decompose && vf->number == SINGULAR && vf->voice == ACTIVE && vf->mood == INDICATIVE)
                {
                    ucs2[(*len) - 2] = GREEK_SMALL_LETTER_ETA_WITH_DASIA;
                }
            }
        }
        else if (vf->voice == MIDDLE)
        {
            if ( utf8HasSuffix(vf->verb->present, "ῑ̔́ημι"))
            {
                if (vf->mood == INDICATIVE || vf->mood == OPTATIVE)
                {
                    ucs2[1] = GREEK_SMALL_LETTER_EPSILON;
                    ucs2[2] = GREEK_SMALL_LETTER_IOTA_WITH_DASIA;
                }
                if (vf->mood == INDICATIVE && decompose)
                {
                    ucsplice(ucs2, len, ucs2Capacity, *len - 1, 1, (UCS2[]){SPACE,HYPHEN,SPACE,GREEK_SMALL_LETTER_EPSILON_WITH_DASIA }, 4);
                }
                if (vf->mood == OPTATIVE)
                {
                    if (!decompose)
                    {
                        ucsplice(ucs2, len, ucs2Capacity, 2, 1, NULL, 0);
                        if (ending[0] == GREEK_SMALL_LETTER_OMICRON)
                        {
                            ucs2[1] = GREEK_SMALL_LETTER_OMICRON;
                        }
                        ucsplice(ending, &elen, ENDING_CAPACITY, 0, 2, (UCS2[]){GREEK_SMALL_LETTER_IOTA_WITH_DASIA}, 1);
                    }
                    else
                    {
                        ucsplice(ucs2, len, ucs2Capacity, 1, 2, (UCS2[]){GREEK_SMALL_LETTER_EPSILON_WITH_DASIA}, 1);
                        if (ending[0] != GREEK_SMALL_LETTER_OMICRON)
                        {
                            ucsplice(ending, &elen, ENDING_CAPACITY, 0, 2, (UCS2[]){GREEK_SMALL_LETTER_IOTA}, 1);
                        }
                    }
                }
                else if (vf->mood == SUBJUNCTIVE)
                {
                    if (!decompose)
                    {
                        ucsplice(ucs2, len, ucs2Capacity, 1, 2, NULL, 0);
                        
                        if (vf->person == FIRST)
                        {
                            if (vf->number == SINGULAR)
                                ending[0] = GREEK_SMALL_LETTER_OMEGA_WITH_DASIA_AND_PERISPOMENI;
                            else
                                ending[0] = GREEK_SMALL_LETTER_OMEGA_WITH_DASIA;
                        }
                        else if (vf->person == SECOND)
                        {
                            if (vf->number == SINGULAR)
                                ending[0] = GREEK_SMALL_LETTER_ETA_WITH_DASIA_AND_PERISPOMENI_AND_YPOGEGRAMMENI;
                            else
                                ending[0] = GREEK_SMALL_LETTER_ETA_WITH_DASIA_AND_PERISPOMENI;
                        }
                        else if (vf->person == THIRD)
                        {
                            if (vf->number == SINGULAR)
                                ending[0] = GREEK_SMALL_LETTER_ETA_WITH_DASIA_AND_PERISPOMENI;
                            else
                                ending[0] = GREEK_SMALL_LETTER_OMEGA_WITH_DASIA_AND_PERISPOMENI;
                        }
                    }
                    else
                    {
                        ucsplice(ucs2, len, ucs2Capacity, 1, 2, (UCS2[]){GREEK_SMALL_LETTER_EPSILON_WITH_DASIA}, 1);
                    }
                }
                else if (vf->mood == IMPERATIVE)
                {
                    if (vf->person == SECOND && vf->number == SINGULAR)
                    {
                        if (!decompose)
                        {
                            ucsplice(ucs2, len, ucs2Capacity, 1, 2, NULL, 0);
                            ucsplice(ending, &elen, ENDING_CAPACITY, 0, 1, (UCS2[]){GREEK_SMALL_LETTER_OMICRON,GREEK_SMALL_LETTER_UPSILON_WITH_DASIA_AND_PERISPOMENI}, 2);
                        }
                        else
                        {
                            ucsplice(ucs2, len, ucs2Capacity, 1, 2, (UCS2[]){GREEK_SMALL_LETTER_EPSILON_WITH_DASIA}, 1);
                            ucsplice(ending, &elen, ENDING_CAPACITY, 0, 1, (UCS2[]){GREEK_SMALL_LETTER_OMICRON,GREEK_SMALL_LETTER_UPSILON}, 2);
                        }
                    }
                    else
                    {
                        ucsplice(ucs2, len, ucs2Capacity, 1, 2, (UCS2[]){GREEK_SMALL_LETTER_EPSILON_WITH_DASIA}, 1);
                    }
                }
            }
            if ( utf8HasSuffix(vf->verb->present, "ῑ́ημι"))
            {
                if (vf->mood == INDICATIVE || vf->mood == OPTATIVE)
                {
                    ucs2[*len - 2] = GREEK_SMALL_LETTER_EPSILON;
                    ucs2[*len - 1] = GREEK_SMALL_LETTER_IOTA;
                }
                if (vf->mood == INDICATIVE && decompose)
                {
                    ucsplice(ucs2, len, ucs2Capacity, *len - 1, 1, (UCS2[]){SPACE,HYPHEN,SPACE,GREEK_SMALL_LETTER_EPSILON_WITH_DASIA }, 4);
                }
                else if (vf->mood == OPTATIVE)
                {
                    if (!decompose)
                    {
                        ucsplice(ucs2, len, ucs2Capacity, *len - 1, 1, NULL, 0);
                        if (ending[0] == GREEK_SMALL_LETTER_OMICRON)
                        {
                            ucs2[*len - 1] = GREEK_SMALL_LETTER_OMICRON;
                        }
                        ucsplice(ending, &elen, ENDING_CAPACITY, 0, 1, NULL, 0);
                    }
                    else
                    {
                        ucsplice(ucs2, len, ucs2Capacity, *len - 1, 1, NULL, 0);
                        ucs2[*len - 1] = GREEK_SMALL_LETTER_EPSILON_WITH_DASIA;
                        if (ending[0] != GREEK_SMALL_LETTER_OMICRON)
                        {
                            ucsplice(ending, &elen, ENDING_CAPACITY, 0, 2, (UCS2[]){GREEK_SMALL_LETTER_IOTA}, 1);
                        }
                    }
                }
                else if (vf->mood == SUBJUNCTIVE)
                {
                    if (!decompose)
                    {
                        ucsplice(ucs2, len, ucs2Capacity, *len - 2, 2, NULL, 0);
                        
                        if (vf->person == FIRST)
                        {
                            if (vf->number == SINGULAR)
                                ending[0] = GREEK_SMALL_LETTER_OMEGA_WITH_PERISPOMENI;
                            else
                                ending[0] = GREEK_SMALL_LETTER_OMEGA;
                        }
                        else if (vf->person == SECOND)
                        {
                            if (vf->number == SINGULAR)
                                ending[0] = GREEK_SMALL_LETTER_ETA_WITH_PERISPOMENI_AND_YPOGEGRAMMENI;
                            else
                                ending[0] = GREEK_SMALL_LETTER_ETA_WITH_PERISPOMENI;
                        }
                        else if (vf->person == THIRD)
                        {
                            if (vf->number == SINGULAR)
                                ending[0] = GREEK_SMALL_LETTER_ETA_WITH_PERISPOMENI;
                            else
                                ending[0] = GREEK_SMALL_LETTER_OMEGA_WITH_PERISPOMENI;
                        }
                    }
                    else
                    {
                        ucsplice(ucs2, len, ucs2Capacity, *len - 2, 2, (UCS2[]){GREEK_SMALL_LETTER_EPSILON_WITH_DASIA}, 1);
                    }
                }
                else if (vf->mood == IMPERATIVE)
                {
                    if (vf->person == SECOND && vf->number == SINGULAR)
                    {
                        if (!decompose)
                        {
                            ucsplice(ucs2, len, ucs2Capacity, *len - 2, 2, NULL, 0);
                            ending[0] = GREEK_SMALL_LETTER_OMICRON;
                            ending[1] = GREEK_SMALL_LETTER_UPSILON_WITH_PERISPOMENI;
                            elen = 2;
                        }
                        else
                        {
                            ucsplice(ucs2, len, ucs2Capacity, *len - 2, 2, (UCS2[]){GREEK_SMALL_LETTER_EPSILON_WITH_DASIA}, 1);
                            ending[0] = GREEK_SMALL_LETTER_OMICRON;
                            ending[1] = GREEK_SMALL_LETTER_UPSILON;
                            elen = 2;
                        }
                    }
                    else
                    {
                        if (decompose)
                            ucsplice(ucs2, len, ucs2Capacity, *len - 2, 2, (UCS2[]){GREEK_SMALL_LETTER_EPSILON_WITH_DASIA}, 1);
                        else
                            ucsplice(ucs2, len, ucs2Capacity, *len - 2, 2, (UCS2[]){GREEK_SMALL_LETTER_EPSILON}, 1);
                    }
                }
            }
            else if ( utf8HasSuffix(vf->verb->present, "τίθημι") )
            {
                (*len) -= 1;
                ucs2[*len - 1] = GREEK_SMALL_LETTER_EPSILON;
                if (vf->person == SECOND && vf->number == SINGULAR && vf->mood == INDICATIVE)
                {
                    if (!decompose)
                    {
                        (*len) -= 1;
                        ending[0] = GREEK_SMALL_LETTER_OMICRON;
                        ending[1] = GREEK_SMALL_LETTER_UPSILON;
                    }
                    else
                    {
                        ending[0] = GREEK_SMALL_LETTER_OMICRON;
                        elen = 1;
                    }
                }
                else if (vf->mood == SUBJUNCTIVE)
                {
                    if (!decompose)
                    {
                        (*len) -= 1;
                    }
                }
                else if (vf->mood == OPTATIVE)
                {
                    //exceptional alternates H&Q page 375
                    if (ending[0] == GREEK_SMALL_LETTER_OMICRON)// this is right
                    {
                        if (!decompose)
                        {
                            //ucsplice(ending, &elen, ENDING_CAPACITY, 0, 1, NULL, 0);
                            //ucs2[1] = GREEK_SMALL_LETTER_OMICRON;
                            (*len) -= 1; //fix for anathoito, etc.
                        }
                    }
                    else
                    {
                        ucsplice(ending, &elen, ENDING_CAPACITY, 0, 1, NULL, 0);
                    }
                }
                else if (vf->mood == IMPERATIVE)
                {
                    if (vf->person == SECOND && vf->number == SINGULAR)
                    {
                        if (!decompose)
                        {
                            ucs2[*len - 1] = GREEK_SMALL_LETTER_OMICRON;
                            ending[0] = GREEK_SMALL_LETTER_UPSILON_WITH_PERISPOMENI;
                        }
                        else
                        {
                            ending[0] = GREEK_SMALL_LETTER_OMICRON;
                        }
                    }
                }
            }
            else if ( utf8HasSuffix(vf->verb->present, "δίδωμι") )
            {
                (*len) -= 1;
                ucs2[*len - 1] = GREEK_SMALL_LETTER_OMICRON;
                if (vf->person == SECOND && vf->number == SINGULAR && vf->mood == INDICATIVE)
                {
                    if (!decompose)
                    {
                        ending[0] = GREEK_SMALL_LETTER_UPSILON;
                    }
                    else
                    {
                        ending[0] = GREEK_SMALL_LETTER_OMICRON;
                    }
                    elen = 1;
                }
                else if (vf->mood == SUBJUNCTIVE)
                {
                    if (!decompose)
                    {
                        (*len) -= 1;
                        if (vf->person == SECOND && vf->number == SINGULAR)
                        {
                            ending[0] = GREEK_SMALL_LETTER_OMEGA_WITH_PERISPOMENI_AND_YPOGEGRAMMENI;
                        }
                        else if (vf->person == THIRD && vf->number == SINGULAR)
                        {
                            ending[0] = GREEK_SMALL_LETTER_OMEGA_WITH_PERISPOMENI;
                        }
                        else if (vf->person == SECOND && vf->number == PLURAL)
                        {
                            ending[0] = GREEK_SMALL_LETTER_OMEGA_WITH_PERISPOMENI;
                        }
                    }
                }
                else if (vf->mood == OPTATIVE)
                {
                    //accent doesn't go past syllable with iota
                    //Hardy caught this one: see his email from 02/22/2016
                    if (vf->person == FIRST)
                    {
                        ucsplice(ending, &elen, ENDING_CAPACITY, 0, 1, NULL, 0);
                    }
                    else
                    {
                        ucsplice(ending, &elen, ENDING_CAPACITY, 0, 2, (UCS2[]){GREEK_SMALL_LETTER_IOTA_WITH_PERISPOMENI}, 1);
                    }
                }
                else if (vf->mood == IMPERATIVE)
                {
                    if (vf->person == SECOND && vf->number == SINGULAR)
                    {
                        if (decompose)
                        {
                            ending[0] = GREEK_SMALL_LETTER_OMICRON;
                        }
                        else
                        {
                            //Fix me.  See H&Q p. 376 for note on accentuation when prefixed
                            if (utf8HasSuffix(vf->verb->present, "μεταδίδωμι"))
                                ending[0] = GREEK_SMALL_LETTER_UPSILON;
                            else
                                ending[0] = GREEK_SMALL_LETTER_UPSILON_WITH_PERISPOMENI;
                        }
                        elen = 1;
                    }
                }
            }
        }
    }
    /* start root aorists */
    else if (vf->tense == AORIST && (utf8HasSuffix(vf->verb->present, "φθάνω") || utf8HasSuffix(vf->verb->present, "βαίνω")) &&  ucs2[*len -1] == GREEK_SMALL_LETTER_ETA )
    {
        //root aorist
        if (vf->mood == SUBJUNCTIVE)
        {
            if (decompose)
            {
                ucs2[(*len) - 1] = GREEK_SMALL_LETTER_EPSILON; //yes epsilon
            }
            else
            {
                (*len) -= 1;
            }
        }
        else if (vf->mood == OPTATIVE)
        {
            ucs2[*len - 1] = GREEK_SMALL_LETTER_ALPHA;
            ucsplice(ending, &elen, ENDING_CAPACITY, 0, 1, NULL, 0);
        }
        else if (vf->mood == IMPERATIVE)
        {
            if (vf->person == THIRD && vf->number == PLURAL)
                ucs2[*len - 1] = GREEK_SMALL_LETTER_ALPHA;
            else if (vf->person == SECOND && vf->number == SINGULAR && !utf8HasSuffix(vf->verb->present, "βαίνω"))
                ending[0] = GREEK_SMALL_LETTER_TAU; //disimilation of aspirates here, right? fix me?
        }
    }
    else if (vf->tense == AORIST && utf8HasSuffix(vf->verb->present, "γιγνώσκω") && vf->voice == ACTIVE)
    {
        //root aorist
        if (vf->mood == SUBJUNCTIVE)
        {
            if (decompose)
            {
                ucs2[(*len) - 1] = GREEK_SMALL_LETTER_OMICRON; //see h&q page 463, just like didwmi
            }
            else
            {
                (*len) -= 1;
                if (vf->person == SECOND && vf->number == SINGULAR)
                    ending[0] = GREEK_SMALL_LETTER_OMEGA_WITH_PERISPOMENI_AND_YPOGEGRAMMENI;
                else if (vf->person == THIRD && vf->number == SINGULAR)
                    ending[0] = GREEK_SMALL_LETTER_OMEGA_WITH_PERISPOMENI_AND_YPOGEGRAMMENI;
                else if (vf->person == SECOND && vf->number == PLURAL)
                    ending[0] = GREEK_SMALL_LETTER_OMEGA_WITH_PERISPOMENI;
            }
        }
        else if (vf->mood == OPTATIVE)
        {
            ucs2[*len - 1] = GREEK_SMALL_LETTER_OMICRON;
            ucsplice(ending, &elen, ENDING_CAPACITY, 0, 1, NULL, 0);
        }
        else if (vf->mood == IMPERATIVE)
        {
            if (vf->person == THIRD && vf->number == PLURAL)
                ucs2[*len - 1] = GREEK_SMALL_LETTER_OMICRON;
            //else if (vf->person == SECOND && vf->number == SINGULAR)
            //    ending[0] = GREEK_SMALL_LETTER_TAU; //disimilation of aspirates here, right? fix me?
        }
        
    }
    else if ( ( utf8HasSuffix(vf->verb->present, "στημι") || utf8HasSuffix(vf->verb->present, "σταμαι")) && vf->tense == PERFECT)
    {
        if (vf->number == PLURAL)
        {
            (*len) -= 1;
            ucs2[*len -1] = GREEK_SMALL_LETTER_ALPHA;
            
            if (vf->person == THIRD)
            {
                if (!decompose)
                {
                    (*len) -= 1;
                    ucsplice(ending, &elen, ENDING_CAPACITY, 0, 2, (UCS2[]){GREEK_SMALL_LETTER_ALPHA_WITH_PERISPOMENI}, 1);
                }
            }
            else
            {
                ucsplice(ending, &elen, ENDING_CAPACITY, 0, 1, NULL, 0);
            }
        }
    }
    else if ( ( utf8HasSuffix(vf->verb->present, "στημι") || utf8HasSuffix(vf->verb->present, "σταμαι")) && vf->tense == PLUPERFECT)
    {
        //H&Q p. 378
        if (vf->number == PLURAL)
        {
            (*len) -= 1;
            ucs2[*len - 1] = GREEK_SMALL_LETTER_ALPHA;
            if (vf->person == FIRST)
            {
                ucsplice(ending, &elen, ENDING_CAPACITY, 0, 1, NULL, 0);
            }
            else if (vf->person == SECOND)
            {
                ucsplice(ending, &elen, ENDING_CAPACITY, 0, 1, NULL, 0);
            }
            else if (vf->person == THIRD)
            {
                ucsplice(ending, &elen, ENDING_CAPACITY, 0, 1, NULL, 0);
            }
        }
    }
    else if (utf8HasSuffix(vf->verb->present, "εἰμί") && vf->tense == FUTURE && vf->person == THIRD && vf->number == SINGULAR && vf->mood == INDICATIVE)
    {
        if (!decompose)
            ucsplice(ending, &elen, ENDING_CAPACITY, 0, 1, NULL, 0);
    }
    else if (utf8HasSuffix(vf->verb->present, "ἔχω") && vf->number == SINGULAR && vf->tense == AORIST && vf->voice == ACTIVE && vf->mood == OPTATIVE)
    {   //h&q page 504
        ending[0] = GREEK_SMALL_LETTER_OMICRON;
    }
    else if (utf8HasSuffix(vf->verb->present, "ἔχω") && vf->person == SECOND && vf->number == SINGULAR && vf->tense == AORIST && vf->voice == ACTIVE && vf->mood == IMPERATIVE)
    {   //h&q page 504
        elen++;
        ending[1] = GREEK_SMALL_LETTER_FINAL_SIGMA;
    }
    else if (utf8HasSuffix(vf->verb->present, "κεῖμαι"))
    {
        if ((vf->mood == SUBJUNCTIVE || vf->mood == OPTATIVE) && vf->tense == PRESENT)
        {
            ucsplice(ucs2, len, ucs2Capacity, *len - 1, 1, NULL, 0);
        }
        if (vf->mood == IMPERATIVE && vf->person == SECOND && vf->number == SINGULAR)
        {
            ending[0] = GREEK_SMALL_LETTER_SIGMA;
            ending[1] = GREEK_SMALL_LETTER_OMICRON;
            elen = 2;
        }
    }
    
    //Aorist passive imperative 2nd sing.
    if (vf->person == SECOND && vf->number == SINGULAR && vf->tense == AORIST && vf->voice == PASSIVE && vf->mood == IMPERATIVE && !decompose)
    {
        //determine which aorist passive imperative ending
        if (ucs2[*len - 1] == GREEK_SMALL_LETTER_CHI || ucs2[*len - 1] == GREEK_SMALL_LETTER_PHI || ucs2[*len - 1] == GREEK_SMALL_LETTER_THETA)
        {
            ending[1] = GREEK_SMALL_LETTER_TAU;
        }
        else
        {
            ending[1] = GREEK_SMALL_LETTER_THETA;
        }
    }
    
    //add the ending to the stem, decompose if necessary
    if (decompose && *len > 0 && !(*len == 1 && ucs2[0] == '-'))
    {
        ucsplice(ucs2, len, ucs2Capacity, *len, 0, (UCS2[]){SPACE,HYPHEN,SPACE}, 3);
    }
    
    //add the ending
    ucsplice(ucs2, len, ucs2Capacity, *len, 0, ending, elen);
}
