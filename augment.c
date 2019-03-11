//
//  augment.c
//  Hoplite Challenge
//
//  Created by Jeremy March on 3/4/17.
//  Copyright © 2017 Jeremy March. All rights reserved.
//

#include "augment.h"

//we assume accents have been stripped, but not breathings, macrons or iota subscripts
void augmentStem(VerbFormC *vf, UCS2 *ucs2, int *len, int bufferCapacity, bool decompose, int stem)
{
    if (decompose && (vf->verb->verbclass & PREFIXED) != PREFIXED)
    {
        /*
         Don't add an augment on these decomposed forms which start with e, ei, or h
         
         H&Q page 326.  "In most verbs when principal part iv or v begins with e) or ei), the pluperfect is unaugmented."
         */
        if (vf->tense == PLUPERFECT && (ucs2[0] == GREEK_SMALL_LETTER_EPSILON_WITH_PSILI || (ucs2[0] == GREEK_SMALL_LETTER_EPSILON && ucs2[1] == GREEK_SMALL_LETTER_IOTA_WITH_PSILI) || ucs2[0] == GREEK_SMALL_LETTER_ETA_WITH_PSILI || ucs2[0] == GREEK_SMALL_LETTER_ETA_WITH_DASIA || ucs2[0] == GREEK_SMALL_LETTER_ETA_WITH_DASIA_AND_YPOGEGRAMMENI || ucs2[0] == GREEK_SMALL_LETTER_ETA_WITH_PSILI_AND_YPOGEGRAMMENI ))
        {
            return;
        }
        
        if (vf->tense == PLUPERFECT && ucs2[0] == GREEK_SMALL_LETTER_ETA && ucs2[1] == GREEK_SMALL_LETTER_UPSILON_WITH_DASIA)
        {
            return;
        }
        
        if (utf8HasSuffix(vf->verb->present, "εἶμι"))
        {
            splice(ucs2, len, bufferCapacity, 0, 2, (UCS2[]){GREEK_SMALL_LETTER_ETA_WITH_PSILI_AND_YPOGEGRAMMENI}, 1);
            return; //don't do anything with this weird augmenting
        }
        //long iota doesn't get further augment (e.g. ihmi)
        if (ucs2[0] == GREEK_SMALL_LETTER_IOTA && ucs2[1] == COMBINING_MACRON)
        {
            return;
        }
        
        if ((vf->tense == PLUPERFECT && vf->number == SINGULAR && utf8HasSuffix(vf->verb->present, "στημι")) || (vf->tense != PLUPERFECT && utf8HasSuffix(vf->verb->present, "στημι")) || !utf8HasSuffix(vf->verb->present, "στημι"))
        {
            //pluperfect of elau/nw
            if (ucs2[0] == '-' && ucs2[1] == GREEK_SMALL_LETTER_EPSILON_WITH_PSILI)
                return;
            
            if (ucs2[1] == GREEK_SMALL_LETTER_EPSILON && ucs2[2] == GREEK_SMALL_LETTER_IOTA_WITH_DASIA)
                return;
            
            if (ucs2[0] == GREEK_SMALL_LETTER_ETA_WITH_DASIA)
                return;
            
            splice(ucs2, len, bufferCapacity, 0, 0, (UCS2[]){DECOMPOSED_AUGMENT_CHAR,SPACE,HYPHEN,SPACE}, 4);
        }
        return;
    }
    else if (decompose && utf8HasSuffix(vf->verb->present, "ἀποθνῄσκω") && vf->tense == PLUPERFECT)
    {
        splice(ucs2, len, bufferCapacity, 0, 0, (UCS2[]){DECOMPOSED_AUGMENT_CHAR,SPACE,HYPHEN,SPACE}, 4);
        return;
    }
    
    if ((vf->verb->verbclass & PREFIXED) == PREFIXED && !( utf8HasSuffix(vf->verb->present, "ἀποθνῄσκω") && vf->tense == PLUPERFECT) )
    {
        UCS2 ek[] = { GREEK_SMALL_LETTER_EPSILON_WITH_PSILI, GREEK_SMALL_LETTER_KAPPA };
        UCS2 ana[] = { GREEK_SMALL_LETTER_ALPHA_WITH_PSILI, GREEK_SMALL_LETTER_NU, GREEK_SMALL_LETTER_ALPHA };
        UCS2 sum[] = { GREEK_SMALL_LETTER_SIGMA, GREEK_SMALL_LETTER_UPSILON, GREEK_SMALL_LETTER_MU };
        UCS2 sun[] = { GREEK_SMALL_LETTER_SIGMA, GREEK_SMALL_LETTER_UPSILON, GREEK_SMALL_LETTER_NU };
        UCS2 dia[] = { GREEK_SMALL_LETTER_DELTA, GREEK_SMALL_LETTER_IOTA, GREEK_SMALL_LETTER_ALPHA };
        //UCS2 di[] = { GREEK_SMALL_LETTER_DELTA, GREEK_SMALL_LETTER_IOTA };
        UCS2 ape[] = { GREEK_SMALL_LETTER_ALPHA_WITH_PSILI, GREEK_SMALL_LETTER_PI, GREEK_SMALL_LETTER_EPSILON };
        UCS2 apol[] = { GREEK_SMALL_LETTER_ALPHA_WITH_PSILI, GREEK_SMALL_LETTER_PI, GREEK_SMALL_LETTER_OMICRON, GREEK_SMALL_LETTER_LAMDA };
        UCS2 apo[] = { GREEK_SMALL_LETTER_ALPHA_WITH_PSILI, GREEK_SMALL_LETTER_PI, GREEK_SMALL_LETTER_OMICRON };
        UCS2 aph[] = { GREEK_SMALL_LETTER_ALPHA_WITH_PSILI, GREEK_SMALL_LETTER_PHI };
        UCS2 kath[] = { GREEK_SMALL_LETTER_KAPPA, GREEK_SMALL_LETTER_ALPHA, GREEK_SMALL_LETTER_THETA };
        UCS2 kata[] = { GREEK_SMALL_LETTER_KAPPA, GREEK_SMALL_LETTER_ALPHA, GREEK_SMALL_LETTER_TAU, GREEK_SMALL_LETTER_ALPHA };
        UCS2 meta[] = { GREEK_SMALL_LETTER_MU, GREEK_SMALL_LETTER_EPSILON, GREEK_SMALL_LETTER_TAU, GREEK_SMALL_LETTER_ALPHA };
        UCS2 metan[] = { GREEK_SMALL_LETTER_MU, GREEK_SMALL_LETTER_EPSILON, GREEK_SMALL_LETTER_TAU, GREEK_SMALL_LETTER_ALPHA, GREEK_SMALL_LETTER_NU };
        UCS2 epi[] = { GREEK_SMALL_LETTER_EPSILON_WITH_PSILI, GREEK_SMALL_LETTER_PI, GREEK_SMALL_LETTER_IOTA };
        UCS2 epan[] = { GREEK_SMALL_LETTER_EPSILON_WITH_PSILI, GREEK_SMALL_LETTER_PI, GREEK_SMALL_LETTER_ALPHA, GREEK_SMALL_LETTER_NU };
        UCS2 pro[] = { GREEK_SMALL_LETTER_PI, GREEK_SMALL_LETTER_RHO, GREEK_SMALL_LETTER_OMICRON };
        UCS2 para[] = { GREEK_SMALL_LETTER_PI, GREEK_SMALL_LETTER_ALPHA, GREEK_SMALL_LETTER_RHO, GREEK_SMALL_LETTER_ALPHA };
        UCS2 up[] = { GREEK_SMALL_LETTER_UPSILON_WITH_DASIA, GREEK_SMALL_LETTER_PI };
        UCS2 upo[] = { GREEK_SMALL_LETTER_UPSILON_WITH_DASIA, GREEK_SMALL_LETTER_PI,GREEK_SMALL_LETTER_OMICRON };

        if (hasPrefix(ucs2, *len, upo, 3))
        {
            if ( decompose)
            {
                splice(ucs2, len, bufferCapacity, 3, 0, (UCS2[]){SPACE,HYPHEN,SPACE,DECOMPOSED_AUGMENT_CHAR,SPACE,HYPHEN,SPACE}, 7);
            }
            else if (vf->tense == IMPERFECT || vf->tense == PLUPERFECT)
            {
                splice(ucs2, len, bufferCapacity, 2, 1, (UCS2[]){GREEK_SMALL_LETTER_EPSILON}, 1);
            }
        }
        else if (hasPrefix(ucs2, *len, up, 2))
        {
            if ( decompose)
            {
                splice(ucs2, len, bufferCapacity, 2, 0, (UCS2[]){GREEK_SMALL_LETTER_OMICRON, SPACE,HYPHEN,SPACE,DECOMPOSED_AUGMENT_CHAR,SPACE,HYPHEN,SPACE}, 8);
            }
            else if (vf->tense == IMPERFECT || vf->tense == PLUPERFECT)
            {
                splice(ucs2, len, bufferCapacity, 2, 1, (UCS2[]){GREEK_SMALL_LETTER_ETA}, 1);
            }
        }
        else if (hasPrefix(ucs2, *len, para, 4))
        {
            if ( decompose)
            {
                splice(ucs2, len, bufferCapacity, 4, 0, (UCS2[]){SPACE,HYPHEN,SPACE,DECOMPOSED_AUGMENT_CHAR,SPACE,HYPHEN,SPACE}, 7);
            }
            else if (vf->tense == IMPERFECT || vf->tense == PLUPERFECT)
            {
                splice(ucs2, len, bufferCapacity, 3, 1, (UCS2[]){GREEK_SMALL_LETTER_EPSILON}, 1);
            }
        }
        else if (hasPrefix(ucs2, *len, pro, 3))
        {
            if ( decompose)
            {
                splice(ucs2, len, bufferCapacity, 3, 0, (UCS2[]){SPACE,HYPHEN,SPACE}, 3);
                if (vf->tense == AORIST || vf->tense == IMPERFECT || vf->tense == PLUPERFECT)
                {
                    splice(ucs2, len, bufferCapacity, 6, 0, (UCS2[]){DECOMPOSED_AUGMENT_CHAR,SPACE,HYPHEN,SPACE}, 4);
                }
            }
            else if (vf->tense == IMPERFECT || vf->tense == PLUPERFECT)
            {
                if (stem > 0)
                    splice(ucs2, len, bufferCapacity, 3, 0, (UCS2[]){GREEK_SMALL_LETTER_UPSILON}, 1);
                else
                    splice(ucs2, len, bufferCapacity, 3, 0, (UCS2[]){GREEK_SMALL_LETTER_EPSILON}, 1);
            }
        }
        else if (hasPrefix(ucs2, *len, ek, 2))
        {
            if ( decompose)
            {
                splice(ucs2, len, bufferCapacity, 2, 0, (UCS2[]){SPACE,HYPHEN,SPACE}, 3);
                if (vf->tense == AORIST || vf->tense == IMPERFECT || vf->tense == PLUPERFECT)
                {
                    splice(ucs2, len, bufferCapacity, 5, 0, (UCS2[]){DECOMPOSED_AUGMENT_CHAR,SPACE,HYPHEN,SPACE}, 4);
                }
            }
            else if (vf->tense == IMPERFECT || vf->tense == PLUPERFECT)
            {
                splice(ucs2, len, bufferCapacity, 1, 1, (UCS2[]){GREEK_SMALL_LETTER_XI,GREEK_SMALL_LETTER_EPSILON}, 2);
            }
        }
        else if (hasPrefix(ucs2, *len, ana, 3))
        {
            if ( decompose)
            {
                splice(ucs2, len, bufferCapacity, 3, 0, (UCS2[]){SPACE,HYPHEN,SPACE}, 3);
                if (vf->tense == AORIST || vf->tense == IMPERFECT || vf->tense == PLUPERFECT)
                {
                    splice(ucs2, len, bufferCapacity, 6, 0, (UCS2[]){DECOMPOSED_AUGMENT_CHAR,SPACE,HYPHEN,SPACE}, 4);
                }
            }
            else if (vf->tense == IMPERFECT || vf->tense == PLUPERFECT)
            {
                ucs2[2] = GREEK_SMALL_LETTER_EPSILON;
            }
        }
        else if (hasPrefix(ucs2, *len, sum, 3))
        {
            if ( decompose)
            {
                splice(ucs2, len, bufferCapacity, 2, 1, (UCS2[]){GREEK_SMALL_LETTER_NU,SPACE,HYPHEN,SPACE}, 4);
                if (vf->tense == PLUPERFECT || vf->tense == IMPERFECT)
                {
                    splice(ucs2, len, bufferCapacity, 6, 0, (UCS2[]){DECOMPOSED_AUGMENT_CHAR,SPACE,HYPHEN,SPACE}, 4);
                }
            }
            else if (vf->tense == IMPERFECT || vf->tense == PLUPERFECT)
            {
                splice(ucs2, len, bufferCapacity, 2, 1, (UCS2[]){GREEK_SMALL_LETTER_NU,GREEK_SMALL_LETTER_EPSILON}, 2);
            }
        }
        else if (hasPrefix(ucs2, *len, sun, 3))
        {
            if ( decompose)
            {
                splice(ucs2, len, bufferCapacity, 2, 1, (UCS2[]){GREEK_SMALL_LETTER_NU,SPACE,HYPHEN,SPACE}, 4);
                if ((vf->tense == AORIST || vf->tense == IMPERFECT) && !(ucs2[6] == GREEK_SMALL_LETTER_IOTA && ucs2[7] == COMBINING_MACRON))
                {
                    splice(ucs2, len, bufferCapacity, 6, 0, (UCS2[]){DECOMPOSED_AUGMENT_CHAR,SPACE,HYPHEN,SPACE}, 4);
                }
                else if (ucs2[6] == GREEK_SMALL_LETTER_IOTA && ucs2[7] == COMBINING_MACRON)
                {
                    splice(ucs2, len, bufferCapacity, 8, 0, (UCS2[]){COMBINING_ROUGH_BREATHING}, 1);
                }
                else if (vf->tense == PLUPERFECT && ucs2[6] == GREEK_SMALL_LETTER_EPSILON && ucs2[7] == GREEK_SMALL_LETTER_IOTA)
                {
                    ucs2[7] = GREEK_SMALL_LETTER_IOTA_WITH_DASIA;
                }
            }
            else if (vf->tense == IMPERFECT)
            {
                if (!(ucs2[3] == GREEK_SMALL_LETTER_IOTA && ucs2[4] == COMBINING_MACRON))
                {
                    splice(ucs2, len, bufferCapacity, 3, 0, (UCS2[]){GREEK_SMALL_LETTER_EPSILON}, 1);
                }
            }
        }
        else if (hasPrefix(ucs2, *len, dia, 3))
        {
            if ( decompose)
            {
                splice(ucs2, len, bufferCapacity, 3, 0, (UCS2[]){SPACE,HYPHEN,SPACE,DECOMPOSED_AUGMENT_CHAR,SPACE,HYPHEN,SPACE}, 7);
            }
            else
            {
                ucs2[2] = GREEK_SMALL_LETTER_EPSILON;
            }
        }
        else if (hasPrefix(ucs2, *len, epi, 3))
        {
            if ( decompose)
            {
                splice(ucs2, len, bufferCapacity, 3, 0, (UCS2[]){SPACE,HYPHEN,SPACE,DECOMPOSED_AUGMENT_CHAR,SPACE,HYPHEN,SPACE}, 7);
            }
            else
            {
                ucs2[2] = GREEK_SMALL_LETTER_EPSILON;
            }
        }
        else if (hasPrefix(ucs2, *len, ape, 3) && vf->tense == PLUPERFECT && decompose)
        {
            splice(ucs2, len, bufferCapacity, 2, 0, (UCS2[]){GREEK_SMALL_LETTER_OMICRON,SPACE,HYPHEN,SPACE}, 4);
        }
        else if (hasPrefix(ucs2, *len, apol, 4))
        {
            if ( decompose)
            {
                splice(ucs2, len, bufferCapacity, 2, 0, (UCS2[]){GREEK_SMALL_LETTER_OMICRON,SPACE,HYPHEN,SPACE,DECOMPOSED_AUGMENT_CHAR,SPACE,HYPHEN,SPACE}, 8);
            }
            else
            {
                ucs2[2] = GREEK_SMALL_LETTER_OMEGA;
            }
        }
        else if (hasPrefix(ucs2, *len, apo, 3))
        {
            if ( decompose)
            {
                splice(ucs2, len, bufferCapacity, 3, 0, (UCS2[]){SPACE,HYPHEN,SPACE,DECOMPOSED_AUGMENT_CHAR,SPACE,HYPHEN,SPACE}, 7);
            }
            else
            {
                ucs2[2] = GREEK_SMALL_LETTER_EPSILON;
            }
        }
        else if (hasPrefix(ucs2, *len, aph, 2))
        {
            if (decompose)
            {
                splice(ucs2, len, bufferCapacity, 1, 1, (UCS2[]){GREEK_SMALL_LETTER_PI,GREEK_SMALL_LETTER_OMICRON,SPACE,HYPHEN,SPACE}, 5);
                
                if ((vf->tense == PLUPERFECT && vf->number == SINGULAR && utf8HasSuffix(vf->verb->present, "στημι")) || (vf->tense != PLUPERFECT && utf8HasSuffix(vf->verb->present, "στημι")) || (!utf8HasSuffix(vf->verb->present, "στημι") && !utf8HasSuffix(vf->verb->present, "ἀφῑ́ημι") && !(utf8HasSuffix(vf->verb->present, "ἀφικνέομαι") && vf->tense == PLUPERFECT)))
                {
                    splice(ucs2, len, bufferCapacity, 6, 0, (UCS2[]){DECOMPOSED_AUGMENT_CHAR,SPACE,HYPHEN,SPACE}, 4);
                    
                    if (ucs2[10] == GREEK_SMALL_LETTER_IOTA && ucs2[11] == COMBINING_MACRON)
                    {
                        splice(ucs2, len, bufferCapacity, 12, 0, (UCS2[]){COMBINING_ROUGH_BREATHING}, 1);
                    }
                    else if (ucs2[10] == GREEK_SMALL_LETTER_IOTA)
                    {
                        ucs2[10] = GREEK_SMALL_LETTER_IOTA_WITH_DASIA;
                    }
                    else if (ucs2[10] == GREEK_SMALL_LETTER_EPSILON)
                    {
                        ucs2[10] = GREEK_SMALL_LETTER_EPSILON_WITH_DASIA;
                    }
                }
                else
                {
                    if (ucs2[6] == GREEK_SMALL_LETTER_IOTA && ucs2[7] == COMBINING_MACRON)
                    {
                        splice(ucs2, len, bufferCapacity, 8, 0, (UCS2[]){COMBINING_ROUGH_BREATHING}, 1);
                    }
                    else if (ucs2[6] == GREEK_SMALL_LETTER_IOTA)
                    {
                        ucs2[6] = GREEK_SMALL_LETTER_IOTA_WITH_DASIA;
                    }
                    else if (ucs2[6] == GREEK_SMALL_LETTER_EPSILON)
                    {
                        ucs2[6] = GREEK_SMALL_LETTER_EPSILON_WITH_DASIA;
                    }
                }
            }
            else
            {
                //for histhmi pluperfect singular.  H&Q PAGE 378.
                if (vf->tense == PLUPERFECT && (vf->number == SINGULAR || vf->voice != ACTIVE) && utf8HasSuffix(vf->verb->present, "στημι") )
                {
                    splice(ucs2, len, bufferCapacity, 2, 1, (UCS2[]){GREEK_SMALL_LETTER_EPSILON,GREEK_SMALL_LETTER_IOTA}, 2);
                }
                else if (ucs2[2] == GREEK_SMALL_LETTER_IOTA && ucs2[3] != COMBINING_MACRON)
                {
                    splice(ucs2, len, bufferCapacity, 3, 0, (UCS2[]){COMBINING_MACRON}, 1);
                }
            }
        }
        else if (hasPrefix(ucs2, *len, kata, 4))
        {
            if (decompose)
            {
                splice(ucs2, len, bufferCapacity, 4, 0, (UCS2[]){SPACE,HYPHEN,SPACE,DECOMPOSED_AUGMENT_CHAR,SPACE,HYPHEN,SPACE}, 7);
            }
            else
            {
                ucs2[3] = GREEK_SMALL_LETTER_EPSILON;
            }
        }
        else if (hasPrefix(ucs2, *len, kath, 3))
        {
            if (decompose)
            {
                splice(ucs2, len, bufferCapacity, 2, 1, (UCS2[]){GREEK_SMALL_LETTER_TAU,GREEK_SMALL_LETTER_ALPHA, SPACE,HYPHEN,SPACE}, 5);

                if ((vf->tense == PLUPERFECT && vf->number == SINGULAR && utf8HasSuffix(vf->verb->present, "στημι")) || (vf->tense != PLUPERFECT && utf8HasSuffix(vf->verb->present, "στημι")))
                {
                    splice(ucs2, len, bufferCapacity, 7, 0, (UCS2[]){DECOMPOSED_AUGMENT_CHAR, SPACE,HYPHEN,SPACE}, 4);
                    
                    if (ucs2[11] == GREEK_SMALL_LETTER_IOTA)
                    {
                        ucs2[11] = GREEK_SMALL_LETTER_IOTA_WITH_DASIA;
                    }
                    else if (ucs2[11] == GREEK_SMALL_LETTER_EPSILON)
                    {
                        ucs2[11] = GREEK_SMALL_LETTER_EPSILON_WITH_DASIA;
                    }
                }
                else
                {
                    if (ucs2[7] == GREEK_SMALL_LETTER_IOTA)
                    {
                        ucs2[7] = GREEK_SMALL_LETTER_IOTA_WITH_DASIA;
                    }
                    else if (ucs2[7] == GREEK_SMALL_LETTER_EPSILON)
                    {
                        ucs2[7] = GREEK_SMALL_LETTER_EPSILON_WITH_DASIA;
                    }
                }
            }
            else
            {
                if (ucs2[3] == GREEK_SMALL_LETTER_IOTA)
                {
                    splice(ucs2, len, bufferCapacity, 4, 0, (UCS2[]){COMBINING_MACRON}, 1);
                }
                //for histhmi pluperfect singular.  H&Q PAGE 378.
                else if (vf->tense == PLUPERFECT && (vf->number == SINGULAR || vf->voice != ACTIVE) && utf8HasSuffix(vf->verb->present, "στημι") )
                {
                    splice(ucs2, len, bufferCapacity, 3, 1, (UCS2[]){GREEK_SMALL_LETTER_EPSILON,GREEK_SMALL_LETTER_IOTA}, 2);
                }
            }
        }
        else if (hasPrefix(ucs2, *len, metan, 5))
        {
            if (decompose)
            {
                splice(ucs2, len, bufferCapacity, 3, 2, (UCS2[]){GREEK_SMALL_LETTER_ALPHA,SPACE,HYPHEN,SPACE,GREEK_SMALL_LETTER_ALPHA,GREEK_SMALL_LETTER_NU,GREEK_SMALL_LETTER_ALPHA,SPACE,HYPHEN,SPACE}, 10);
                
                if ((vf->tense == PLUPERFECT && vf->number == SINGULAR && utf8HasSuffix(vf->verb->present, "σταμαι")) || (vf->tense != PLUPERFECT && utf8HasSuffix(vf->verb->present, "σταμαι")))
                {
                    splice(ucs2, len, bufferCapacity, 13, 0, (UCS2[]){DECOMPOSED_AUGMENT_CHAR,SPACE,HYPHEN,SPACE}, 4);
                    
                    if (ucs2[17] == GREEK_SMALL_LETTER_IOTA)
                    {
                        ucs2[17] = GREEK_SMALL_LETTER_IOTA_WITH_DASIA;
                    }
                    else if (ucs2[17] == GREEK_SMALL_LETTER_EPSILON)
                    {
                        ucs2[17] = GREEK_SMALL_LETTER_EPSILON_WITH_DASIA;
                    }
                }
                else
                {
                    if (ucs2[13] == GREEK_SMALL_LETTER_IOTA)
                    {
                        ucs2[13] = GREEK_SMALL_LETTER_IOTA_WITH_DASIA;
                    }
                    else if (ucs2[13] == GREEK_SMALL_LETTER_EPSILON)
                    {
                        ucs2[13] = GREEK_SMALL_LETTER_EPSILON_WITH_DASIA;
                    }
                }
            }
            else
            {
                //for histhmi pluperfect singular.  H&Q PAGE 378.
                if (vf->tense == PLUPERFECT && (vf->number == SINGULAR || vf->voice != ACTIVE) && utf8HasSuffix(vf->verb->present, "σταμαι") )
                {
                    splice(ucs2, len, bufferCapacity, 5, 1, (UCS2[]){GREEK_SMALL_LETTER_EPSILON,GREEK_SMALL_LETTER_IOTA}, 2);
                }
                else if (ucs2[5] == GREEK_SMALL_LETTER_IOTA)
                {
                    splice(ucs2, len, bufferCapacity, 6, 0, (UCS2[]){COMBINING_MACRON}, 1);
                }
            }
        }
        else if (hasPrefix(ucs2, *len, epan, 4))
        {
            if (decompose)
            {
                splice(ucs2, len, bufferCapacity, 2, 2, (UCS2[]){GREEK_SMALL_LETTER_IOTA,SPACE,HYPHEN,SPACE,GREEK_SMALL_LETTER_ALPHA,GREEK_SMALL_LETTER_NU,GREEK_SMALL_LETTER_ALPHA,SPACE,HYPHEN,SPACE}, 10);
                
                //isthmi only augments pluperfect in the singular
                if ((vf->tense == PLUPERFECT && vf->number == SINGULAR && utf8HasSuffix(vf->verb->present, "σταμαι")) || (vf->tense != PLUPERFECT && utf8HasSuffix(vf->verb->present, "σταμαι")))
                {
                    splice(ucs2, len, bufferCapacity, 12, 0, (UCS2[]){DECOMPOSED_AUGMENT_CHAR,SPACE,HYPHEN,SPACE}, 4);
                    
                    if (ucs2[16] == GREEK_SMALL_LETTER_IOTA)
                    {
                        ucs2[16] = GREEK_SMALL_LETTER_IOTA_WITH_DASIA;
                    }
                    else if (ucs2[16] == GREEK_SMALL_LETTER_EPSILON)
                    {
                        ucs2[16] = GREEK_SMALL_LETTER_EPSILON_WITH_DASIA;
                    }
                }
                else
                {
                    if (ucs2[12] == GREEK_SMALL_LETTER_IOTA)
                    {
                        ucs2[12] = GREEK_SMALL_LETTER_IOTA_WITH_DASIA;
                    }
                    else if (ucs2[12] == GREEK_SMALL_LETTER_EPSILON)
                    {
                        ucs2[12] = GREEK_SMALL_LETTER_EPSILON_WITH_DASIA;
                    }
                }
            }
            else
            {
                //isthmi only augments pluperfect in the singular
                //for histhmi pluperfect singular.  H&Q PAGE 378.
                if (vf->tense == PLUPERFECT && (vf->number == SINGULAR || vf->voice != ACTIVE) && utf8HasSuffix(vf->verb->present, "σταμαι") )
                {
                    splice(ucs2, len, bufferCapacity, 4, 1, (UCS2[]){GREEK_SMALL_LETTER_EPSILON,GREEK_SMALL_LETTER_IOTA}, 2);
                }
                else if (ucs2[4] == GREEK_SMALL_LETTER_IOTA)
                {
                    splice(ucs2, len, bufferCapacity, 5, 0, (UCS2[]){COMBINING_MACRON}, 1);
                }
            }
        }
        else if (hasPrefix(ucs2, *len, meta, 4))
        {
            if (decompose)
            {
                splice(ucs2, len, bufferCapacity, 4, 0, (UCS2[]){SPACE,HYPHEN,SPACE,DECOMPOSED_AUGMENT_CHAR,SPACE,HYPHEN,SPACE}, 7);
            }
            else
            {
                ucs2[3] =  GREEK_SMALL_LETTER_EPSILON;
            }
        }
    }
    else if (ucs2[0] == GREEK_SMALL_LETTER_ALPHA)
    {
        if (ucs2[1] == GREEK_SMALL_LETTER_IOTA_WITH_PSILI)
        {
            splice(ucs2, len, bufferCapacity, 0, 2, (UCS2[]){GREEK_SMALL_LETTER_ETA_WITH_PSILI_AND_YPOGEGRAMMENI}, 1);
        }
        else if (ucs2[1] == GREEK_SMALL_LETTER_IOTA_WITH_DASIA)
        {
            splice(ucs2, len, bufferCapacity, 0, 2, (UCS2[]){GREEK_SMALL_LETTER_ETA_WITH_DASIA_AND_YPOGEGRAMMENI}, 1);
        }
        else if (ucs2[1] == GREEK_SMALL_LETTER_UPSILON_WITH_PSILI)
        {
            ucs2[0] = GREEK_SMALL_LETTER_ETA;
        }
        else if (ucs2[1] == GREEK_SMALL_LETTER_UPSILON_WITH_DASIA)
        {
            ucs2[0] = GREEK_SMALL_LETTER_ETA;
        }
        else
        {
            ucs2[0] = GREEK_SMALL_LETTER_ETA;
        }
    }
    else if (ucs2[0] == GREEK_SMALL_LETTER_ALPHA_WITH_PSILI)
    {
        ucs2[0] = GREEK_SMALL_LETTER_ETA_WITH_PSILI;
    }
    else if (ucs2[0] == GREEK_SMALL_LETTER_ALPHA_WITH_DASIA)
    {
        ucs2[0] = GREEK_SMALL_LETTER_ETA_WITH_DASIA;
    }
    else if (ucs2[0] == GREEK_SMALL_LETTER_EPSILON)
    {
        if (ucs2[1] == GREEK_SMALL_LETTER_IOTA_WITH_PSILI && vf->tense != PLUPERFECT)
        {
            /*
             H&Q page 326.  "In most verbs when principal part iv or v begins with e) or ei), the pluperfect is unaugmented."
             */
            splice(ucs2, len, bufferCapacity, 0, 2, (UCS2[]){GREEK_SMALL_LETTER_ETA_WITH_PSILI_AND_YPOGEGRAMMENI}, 1);
        }
        else if (ucs2[1] == GREEK_SMALL_LETTER_IOTA_WITH_DASIA)
        {
            splice(ucs2, len, bufferCapacity, 0, 2, (UCS2[]){GREEK_SMALL_LETTER_ETA_WITH_DASIA_AND_YPOGEGRAMMENI}, 1);
        }
        else if (ucs2[1] == GREEK_SMALL_LETTER_UPSILON_WITH_PSILI)
        {
            ucs2[0] = GREEK_SMALL_LETTER_ETA;
        }
        else if (ucs2[1] == GREEK_SMALL_LETTER_UPSILON_WITH_DASIA)
        {
            ucs2[0] = GREEK_SMALL_LETTER_ETA;
        }
        /* //probably don't need this, since it's either a diphthong or will have psili or dasia
         else if ( vf->tense != PLUPERFECT ) //because ei) in pluperfect will fall through to this, so need this if
         {
         ucs2[0] = GREEK_SMALL_LETTER_ETA;
         }
         */
    }
    else if (ucs2[0] == GREEK_SMALL_LETTER_EPSILON_WITH_PSILI && vf->tense != PLUPERFECT)
    {
        /*
         H&Q page 326.  "In most verbs when principal part iv or v begins with e) or ei), the pluperfect is unaugmented."
         */
        if (utf8HasSuffix(vf->verb->present, "ἔχω"))
        {
            splice(ucs2, len, bufferCapacity, 0, 1, (UCS2[]){GREEK_SMALL_LETTER_EPSILON,GREEK_SMALL_LETTER_IOTA_WITH_PSILI}, 2);
        }
        else
        {
            ucs2[0] = GREEK_SMALL_LETTER_ETA_WITH_PSILI;
        }
    }
    else if (ucs2[0] == GREEK_SMALL_LETTER_EPSILON_WITH_DASIA)
    {
        //for histhmi pluperfect singular.  H&Q PAGE 378.
        if (vf->tense == PLUPERFECT && (vf->number == SINGULAR || vf->voice != ACTIVE) && ( utf8HasSuffix(vf->verb->present, "στημι") || utf8HasSuffix(vf->verb->present, "σταμαι")))
        {
            splice(ucs2, len, bufferCapacity, 0, 1, (UCS2[]){GREEK_SMALL_LETTER_EPSILON,GREEK_SMALL_LETTER_IOTA_WITH_DASIA}, 2);
        }
        else if (vf->tense == IMPERFECT)
        {
            splice(ucs2, len, bufferCapacity, 0, 1, (UCS2[]){GREEK_SMALL_LETTER_EPSILON,GREEK_SMALL_LETTER_IOTA_WITH_DASIA}, 2);
        }
    }
    else if (ucs2[0] == GREEK_SMALL_LETTER_IOTA && ucs2[1] != COMBINING_MACRON)
    {
        splice(ucs2, len, bufferCapacity, 0, 1, (UCS2[]){GREEK_SMALL_LETTER_IOTA,COMBINING_MACRON}, 2);
    }
    else if (ucs2[0] == GREEK_SMALL_LETTER_IOTA_WITH_PSILI)
    {
        splice(ucs2, len, bufferCapacity, 0, 1, (UCS2[]){GREEK_SMALL_LETTER_IOTA,COMBINING_MACRON,COMBINING_SMOOTH_BREATHING}, 3);
    }
    else if (ucs2[0] == GREEK_SMALL_LETTER_IOTA_WITH_DASIA)
    {
        splice(ucs2, len, bufferCapacity, 0, 1, (UCS2[]){GREEK_SMALL_LETTER_IOTA,COMBINING_MACRON,COMBINING_ROUGH_BREATHING}, 3);
    }
    else if (ucs2[0] == GREEK_SMALL_LETTER_OMICRON)
    {
        if (ucs2[1] == GREEK_SMALL_LETTER_IOTA_WITH_PSILI)
        {
            splice(ucs2, len, bufferCapacity, 0, 1, (UCS2[]){GREEK_SMALL_LETTER_OMEGA_WITH_PSILI_AND_YPOGEGRAMMENI}, 1);
        }
        else if (ucs2[1] == GREEK_SMALL_LETTER_IOTA_WITH_DASIA)
        {
            splice(ucs2, len, bufferCapacity, 0, 1, (UCS2[]){GREEK_SMALL_LETTER_OMEGA_WITH_DASIA_AND_YPOGEGRAMMENI}, 1);
        }
        else
        {
            ucs2[0] = GREEK_SMALL_LETTER_OMEGA;
        }
    }
    else if (ucs2[0] == GREEK_SMALL_LETTER_OMICRON_WITH_PSILI)
    {
        ucs2[0] = GREEK_SMALL_LETTER_OMEGA_WITH_PSILI;
    }
    else if (ucs2[0] == GREEK_SMALL_LETTER_OMICRON_WITH_DASIA && vf->tense == IMPERFECT && utf8HasSuffix(vf->verb->present, "ὁράω") )
    {
        //h&q page 449
        splice(ucs2, len, bufferCapacity, 0, 1, (UCS2[]){GREEK_SMALL_LETTER_EPSILON_WITH_DASIA,GREEK_SMALL_LETTER_OMEGA}, 2);
    }
    else if (ucs2[0] == GREEK_SMALL_LETTER_OMICRON_WITH_DASIA)
    {
        ucs2[0] = GREEK_SMALL_LETTER_OMEGA_WITH_DASIA;
    }
    else if (ucs2[0] == GREEK_SMALL_LETTER_UPSILON)
    {
        splice(ucs2, len, bufferCapacity, 0, 1, (UCS2[]){GREEK_SMALL_LETTER_UPSILON,COMBINING_MACRON}, 2);
    }
    else if (ucs2[0] == GREEK_SMALL_LETTER_UPSILON_WITH_PSILI)
    {
        splice(ucs2, len, bufferCapacity, 0, 2, (UCS2[]){GREEK_SMALL_LETTER_UPSILON,COMBINING_MACRON,COMBINING_SMOOTH_BREATHING}, 3);
    }
    else if (ucs2[0] == GREEK_SMALL_LETTER_UPSILON_WITH_DASIA)
    {
        splice(ucs2, len, bufferCapacity, 0, 2, (UCS2[]){GREEK_SMALL_LETTER_UPSILON,COMBINING_MACRON,COMBINING_ROUGH_BREATHING}, 3);
    }
    else if (isConsonant(ucs2[0]))
    {
        splice(ucs2, len, bufferCapacity, 0, 0, (UCS2[]){GREEK_SMALL_LETTER_EPSILON_WITH_PSILI}, 1);
    }
}

void stripAugmentFromPrincipalPart(VerbFormC *vf, UCS2 *ucs2, int *len, int bufferCapacity, UCS2 presentStemInitial, bool decompose)
{
    UCS2 err[] = { GREEK_SMALL_LETTER_EPSILON_WITH_PSILI, GREEK_SMALL_LETTER_RHO, GREEK_SMALL_LETTER_RHO };
    if ((vf->verb->verbclass & PREFIXED) == PREFIXED)
    {
        UCS2 ex[] = { GREEK_SMALL_LETTER_EPSILON_WITH_PSILI, GREEK_SMALL_LETTER_XI };
        UCS2 ane[] = { GREEK_SMALL_LETTER_ALPHA_WITH_PSILI, GREEK_SMALL_LETTER_NU, GREEK_SMALL_LETTER_EPSILON };
        UCS2 anh[] = { GREEK_SMALL_LETTER_ALPHA_WITH_PSILI, GREEK_SMALL_LETTER_NU, GREEK_SMALL_LETTER_ETA };
        UCS2 sum[] = { GREEK_SMALL_LETTER_SIGMA, GREEK_SMALL_LETTER_UPSILON, GREEK_SMALL_LETTER_MU };
        UCS2 sun[] = { GREEK_SMALL_LETTER_SIGMA, GREEK_SMALL_LETTER_UPSILON, GREEK_SMALL_LETTER_NU };
        UCS2 dia[] = { GREEK_SMALL_LETTER_DELTA, GREEK_SMALL_LETTER_IOTA, GREEK_SMALL_LETTER_ALPHA };
        UCS2 dih[] = { GREEK_SMALL_LETTER_DELTA, GREEK_SMALL_LETTER_IOTA, GREEK_SMALL_LETTER_ETA };
        //UCS2 di[] = { GREEK_SMALL_LETTER_DELTA, GREEK_SMALL_LETTER_IOTA };
        UCS2 apw[] = { GREEK_SMALL_LETTER_ALPHA_WITH_PSILI, GREEK_SMALL_LETTER_PI, GREEK_SMALL_LETTER_OMEGA };
        UCS2 apo[] = { GREEK_SMALL_LETTER_ALPHA_WITH_PSILI, GREEK_SMALL_LETTER_PI, GREEK_SMALL_LETTER_EPSILON };
        UCS2 aph[] = { GREEK_SMALL_LETTER_ALPHA_WITH_PSILI, GREEK_SMALL_LETTER_PHI };
        UCS2 kath[] = { GREEK_SMALL_LETTER_KAPPA, GREEK_SMALL_LETTER_ALPHA, GREEK_SMALL_LETTER_THETA };
        UCS2 kate[] = { GREEK_SMALL_LETTER_KAPPA, GREEK_SMALL_LETTER_ALPHA, GREEK_SMALL_LETTER_TAU, GREEK_SMALL_LETTER_EPSILON };
        UCS2 meta[] = { GREEK_SMALL_LETTER_MU, GREEK_SMALL_LETTER_EPSILON, GREEK_SMALL_LETTER_TAU, GREEK_SMALL_LETTER_ALPHA };
        UCS2 mete[] = { GREEK_SMALL_LETTER_MU, GREEK_SMALL_LETTER_EPSILON, GREEK_SMALL_LETTER_TAU, GREEK_SMALL_LETTER_EPSILON };
        UCS2 metan[] = { GREEK_SMALL_LETTER_MU, GREEK_SMALL_LETTER_EPSILON, GREEK_SMALL_LETTER_TAU, GREEK_SMALL_LETTER_ALPHA, GREEK_SMALL_LETTER_NU };
        UCS2 epan[] = { GREEK_SMALL_LETTER_EPSILON_WITH_PSILI, GREEK_SMALL_LETTER_PI, GREEK_SMALL_LETTER_ALPHA, GREEK_SMALL_LETTER_NU };
        UCS2 ep[] = { GREEK_SMALL_LETTER_EPSILON_WITH_PSILI, GREEK_SMALL_LETTER_PI };
        UCS2 pro[] = { GREEK_SMALL_LETTER_PI, GREEK_SMALL_LETTER_RHO, GREEK_SMALL_LETTER_OMICRON };
        UCS2 par[] = { GREEK_SMALL_LETTER_PI, GREEK_SMALL_LETTER_ALPHA, GREEK_SMALL_LETTER_RHO };
        UCS2 up[] = { GREEK_SMALL_LETTER_UPSILON_WITH_DASIA, GREEK_SMALL_LETTER_PI };
        UCS2 upe[] = { GREEK_SMALL_LETTER_UPSILON_WITH_DASIA, GREEK_SMALL_LETTER_PI,GREEK_SMALL_LETTER_EPSILON };
        
        if (hasPrefix(ucs2, *len, upe, 3))
        {
            if (decompose)
            {
                if (vf->tense == AORIST)
                {
                    splice(ucs2, len, bufferCapacity, 2, 1, (UCS2[]){GREEK_SMALL_LETTER_OMICRON,SPACE,HYPHEN,SPACE}, 4);
                    if (vf->mood == INDICATIVE)
                    {
                        splice(ucs2, len, bufferCapacity, 6, 0, (UCS2[]){DECOMPOSED_AUGMENT_CHAR,SPACE,HYPHEN,SPACE}, 4);
                    }
                }
                else if (vf->tense == FUTURE && vf->voice == PASSIVE)
                {
                    splice(ucs2, len, bufferCapacity, 2, 1, (UCS2[]){GREEK_SMALL_LETTER_OMICRON,SPACE,HYPHEN,SPACE}, 4);
                }
            }
            else if ((vf->tense == AORIST && vf->mood != INDICATIVE) || (vf->tense == FUTURE && vf->voice == PASSIVE))
            {
                splice(ucs2, len, bufferCapacity, 2, 1, (UCS2[]){GREEK_SMALL_LETTER_OMICRON}, 1);
            }
        }
        else if (hasPrefix(ucs2, *len, up, 2))
        {
            if (decompose)
            {
                if (vf->tense == AORIST)
                {
                    splice(ucs2, len, bufferCapacity, 2, 1, (UCS2[]){GREEK_SMALL_LETTER_OMICRON,SPACE,HYPHEN,SPACE,GREEK_SMALL_LETTER_ALPHA}, 5);
                    if (vf->mood == INDICATIVE)
                    {
                        splice(ucs2, len, bufferCapacity, 6, 0, (UCS2[]){DECOMPOSED_AUGMENT_CHAR,SPACE,HYPHEN,SPACE}, 4);
                    }
                }
                else if (vf->tense == FUTURE && vf->voice == PASSIVE)
                {
                    splice(ucs2, len, bufferCapacity, 2, 1, (UCS2[]){GREEK_SMALL_LETTER_OMICRON,SPACE,HYPHEN,SPACE,GREEK_SMALL_LETTER_ALPHA}, 5);
                }
            }
            else if ((vf->tense == AORIST && vf->mood != INDICATIVE) || (vf->tense == FUTURE && vf->voice == PASSIVE))
            {
                splice(ucs2, len, bufferCapacity, 2, 1, (UCS2[]){GREEK_SMALL_LETTER_ALPHA}, 1);
            }
        }
        else if (hasPrefix(ucs2, *len, par, 3))
        {
            if (decompose)
            {
                if (vf->tense == AORIST)
                {
                    splice(ucs2, len, bufferCapacity, 3, 1, (UCS2[]){GREEK_SMALL_LETTER_ALPHA,SPACE,HYPHEN,SPACE}, 4);
                    if (vf->mood == INDICATIVE)
                    {
                        splice(ucs2, len, bufferCapacity, 7, 0, (UCS2[]){DECOMPOSED_AUGMENT_CHAR,SPACE,HYPHEN,SPACE}, 4);
                    }
                }
                else if (vf->tense == FUTURE && vf->voice == PASSIVE)
                {
                    splice(ucs2, len, bufferCapacity, 3, 1, (UCS2[]){GREEK_SMALL_LETTER_ALPHA,SPACE,HYPHEN,SPACE}, 4);
                }
            }
            else if ((vf->tense == AORIST && vf->mood != INDICATIVE) || (vf->tense == FUTURE && vf->voice == PASSIVE))
            {
                splice(ucs2, len, bufferCapacity, 3, 1, (UCS2[]){GREEK_SMALL_LETTER_ALPHA}, 1);
            }
        }
        else if (hasPrefix(ucs2, *len, pro, 3))
        {
            if (decompose)
            {
                if (vf->tense == AORIST)
                {
                    splice(ucs2, len, bufferCapacity, 3, 1, (UCS2[]){SPACE,HYPHEN,SPACE}, 3);
                    if (vf->mood == INDICATIVE)
                    {
                        splice(ucs2, len, bufferCapacity, 6, 0, (UCS2[]){DECOMPOSED_AUGMENT_CHAR,SPACE,HYPHEN,SPACE}, 4);
                    }
                    else if (vf->tense == AORIST || vf->tense == FUTURE)
                    {
                        //ucs2[6] = GREEK_SMALL_LETTER_EPSILON;
                    }
                }
                else
                {
                    //ucs2[6] = GREEK_SMALL_LETTER_EPSILON;
                    splice(ucs2, len, bufferCapacity, 3, 1, (UCS2[]){SPACE,HYPHEN,SPACE}, 3);
                    //splice(ucs2, len, bufferCapacity, 6, 1, NULL, 0);
                }
            }
            else if ((vf->tense == AORIST && vf->mood != INDICATIVE) || vf->tense == FUTURE)
            {
                //ucs2[2] = GREEK_SMALL_LETTER_ALPHA;
                splice(ucs2, len, bufferCapacity, 3, 1, NULL, 0);
            }
        }
        else if (hasPrefix(ucs2, *len, ex, 2))
        {
            if (decompose)
            {
                if (vf->tense == AORIST)
                {
                    splice(ucs2, len, bufferCapacity, 1, 1, (UCS2[]){GREEK_SMALL_LETTER_KAPPA,SPACE,HYPHEN,SPACE}, 4);
                    if (vf->mood == INDICATIVE)
                    {
                        splice(ucs2, len, bufferCapacity, 5, 1, (UCS2[]){DECOMPOSED_AUGMENT_CHAR,SPACE,HYPHEN,SPACE}, 4);
                    }
                    else
                    {
                        splice(ucs2, len, bufferCapacity, 5, 1, NULL, 0);
                    }
                }
            }
            else if ((vf->tense == AORIST && vf->mood != INDICATIVE) || vf->tense == FUTURE)
            {
                splice(ucs2, len, bufferCapacity, 1, 2, (UCS2[]){GREEK_SMALL_LETTER_KAPPA}, 1);
            }
        }
        else if (hasPrefix(ucs2, *len, ane, 3))
        {
            if (decompose)
            {
                if (vf->tense == AORIST)
                {
                    splice(ucs2, len, bufferCapacity, 2, 1, (UCS2[]){GREEK_SMALL_LETTER_ALPHA,SPACE,HYPHEN,SPACE}, 4);
                    if (vf->mood == INDICATIVE)
                    {
                        splice(ucs2, len, bufferCapacity, 6, 0, (UCS2[]){DECOMPOSED_AUGMENT_CHAR,SPACE,HYPHEN,SPACE}, 4);
                    }
                }
                else
                {
                    splice(ucs2, len, bufferCapacity, 2, 1, (UCS2[]){GREEK_SMALL_LETTER_ALPHA,SPACE,HYPHEN,SPACE}, 4);
                }
            }
            else if ((vf->tense == AORIST && vf->mood != INDICATIVE) || vf->tense == FUTURE)
            {
                ucs2[2] = GREEK_SMALL_LETTER_ALPHA;
            }
        }
        else if (hasPrefix(ucs2, *len, anh, 3))
        {
            if (decompose)
            {
                if (vf->tense == AORIST)
                {
                    splice(ucs2, len, bufferCapacity, 2, 1, (UCS2[]){GREEK_SMALL_LETTER_ALPHA,SPACE,HYPHEN,SPACE,GREEK_SMALL_LETTER_EPSILON}, 5);
                    if (vf->mood == INDICATIVE)
                    {
                        splice(ucs2, len, bufferCapacity, 6, 0, (UCS2[]){DECOMPOSED_AUGMENT_CHAR,SPACE,HYPHEN,SPACE }, 4);
                    }
                }
                else
                {
                    ucs2[6] = GREEK_SMALL_LETTER_EPSILON;
                }
            }
            else if ((vf->tense == AORIST && vf->mood != INDICATIVE) || vf->tense == FUTURE)
            {
                ucs2[2] = GREEK_SMALL_LETTER_EPSILON;
            }
        }
        else if (hasPrefix(ucs2, *len, sum, 3))
        {
            if (decompose)
            {
                if (vf->tense == AORIST)
                {
                    splice(ucs2, len, bufferCapacity, 2, 1, (UCS2[]){GREEK_SMALL_LETTER_NU,SPACE,HYPHEN,SPACE}, 4);
                    if (vf->mood == INDICATIVE)
                    {
                        splice(ucs2, len, bufferCapacity, 6, 0, (UCS2[]){DECOMPOSED_AUGMENT_CHAR,SPACE,HYPHEN,SPACE,GREEK_SMALL_LETTER_EPSILON}, 5);
                    }
                    else if (vf->tense == AORIST || vf->tense == FUTURE)
                    {
                        ucs2[6] = GREEK_SMALL_LETTER_EPSILON;
                    }
                }
                else
                {
                    ucs2[6] = GREEK_SMALL_LETTER_EPSILON;
                }
            }
            else if ((vf->tense == AORIST && vf->mood != INDICATIVE) || vf->tense == FUTURE)
            {
                ucs2[3] = GREEK_SMALL_LETTER_EPSILON;
            }
        }
        else if (hasPrefix(ucs2, *len, sun, 3))
        {
            if (decompose)
            {
                if (vf->tense == AORIST)
                {
                    splice(ucs2, len, bufferCapacity, 2, 1, (UCS2[]){GREEK_SMALL_LETTER_NU,SPACE,HYPHEN,SPACE}, 4);
                    
                    if (utf8HasSuffix(vf->verb->present, "συμβουλεύω") && vf->mood == INDICATIVE)
                    {
                        splice(ucs2, len, bufferCapacity, 6, 1, (UCS2[]){DECOMPOSED_AUGMENT_CHAR,SPACE,HYPHEN,SPACE}, 4);
                    }
                    else if (vf->mood == INDICATIVE && !(ucs2[6] == GREEK_SMALL_LETTER_ETA && ucs2[7] == GREEK_SMALL_LETTER_KAPPA && (vf->number == SINGULAR || vf->voice == MIDDLE)))
                    {
                        splice(ucs2, len, bufferCapacity, 6, 1, (UCS2[]){DECOMPOSED_AUGMENT_CHAR,SPACE,HYPHEN,SPACE,GREEK_SMALL_LETTER_EPSILON}, 5);
                        
                        if (ucs2[10] == GREEK_SMALL_LETTER_EPSILON && ucs2[11] == GREEK_SMALL_LETTER_IOTA && vf->voice == PASSIVE)
                        {
                            splice(ucs2, len, bufferCapacity, 10, 2, (UCS2[]){GREEK_SMALL_LETTER_EPSILON_WITH_DASIA}, 1);
                        }
                    }
                    else if (ucs2[6] == GREEK_SMALL_LETTER_EPSILON && ucs2[7] == GREEK_SMALL_LETTER_IOTA) //sunihmi
                    {
                        splice(ucs2, len, bufferCapacity, 6, 2, (UCS2[]){GREEK_SMALL_LETTER_EPSILON_WITH_DASIA}, 1);
                    }
                    else if (ucs2[6] == GREEK_SMALL_LETTER_ETA) //sunferw
                    {
                        ucs2[6] = GREEK_SMALL_LETTER_EPSILON;
                    }
                    else
                    {
                        splice(ucs2, len, bufferCapacity, 6, 1, NULL, 0); //remove augment
                    }
                }
                else
                {
                    splice(ucs2, len, bufferCapacity, 3, 0, (UCS2[]){SPACE,HYPHEN,SPACE}, 3);
                    if (utf8HasSuffix(vf->verb->present, "συμβουλεύω") && vf->tense == FUTURE)
                    {
                        splice(ucs2, len, bufferCapacity, 6, 1, NULL, 0);
                    }
                    else if (ucs2[6] == GREEK_SMALL_LETTER_EPSILON && ucs2[7] == GREEK_SMALL_LETTER_IOTA)
                    {
                        splice(ucs2, len, bufferCapacity, 6, 2, (UCS2[]){GREEK_SMALL_LETTER_EPSILON_WITH_DASIA}, 1);
                    }
                    else if (ucs2[6] == GREEK_SMALL_LETTER_EPSILON && ucs2[7] == GREEK_SMALL_LETTER_IOTA_WITH_DASIA)
                    {
                        splice(ucs2, len, bufferCapacity, 6, 2, (UCS2[]){GREEK_SMALL_LETTER_EPSILON_WITH_DASIA}, 1);
                    }
                    else
                    {
                        ucs2[6] = GREEK_SMALL_LETTER_EPSILON;
                    }
                }
            }
            else if ((vf->tense == AORIST && vf->mood != INDICATIVE) || vf->tense == FUTURE)
            {
                if (ucs2[3] == GREEK_SMALL_LETTER_EPSILON && ucs2[4] == GREEK_SMALL_LETTER_IOTA)
                {
                    splice(ucs2, len, bufferCapacity, 4, 1, NULL, 0);
                }
                else if (ucs2[3] == GREEK_SMALL_LETTER_ETA) //sunferw
                {
                    ucs2[3] = GREEK_SMALL_LETTER_EPSILON;
                }
                else if (ucs2[3] == GREEK_SMALL_LETTER_EPSILON && ucs2[4] == GREEK_SMALL_LETTER_BETA) //SUMBOYLEYW
                {
                    splice(ucs2, len, bufferCapacity, 2, 2, (UCS2[]){GREEK_SMALL_LETTER_MU}, 1);
                }
                else
                {
                    splice(ucs2, len, bufferCapacity, 3, 1, NULL, 0);
                }
            }
        }
        else if (hasPrefix(ucs2, *len, dih, 3))
        {
            if (decompose)
            {
                splice(ucs2, len, bufferCapacity, 2, 1, (UCS2[]){GREEK_SMALL_LETTER_ALPHA,SPACE,HYPHEN,SPACE}, 4);
                
                if (vf->tense == AORIST && vf->mood == INDICATIVE)
                {
                    splice(ucs2, len, bufferCapacity, 6, 0, (UCS2[]){DECOMPOSED_AUGMENT_CHAR,SPACE,HYPHEN,SPACE,GREEK_SMALL_LETTER_EPSILON}, 5);
                }
                else if (vf->tense == AORIST || vf->tense == FUTURE)
                {
                    splice(ucs2, len, bufferCapacity, 6, 0, (UCS2[]){GREEK_SMALL_LETTER_EPSILON}, 1);
                }
            }
            else
            {
                ucs2[2] = GREEK_SMALL_LETTER_EPSILON;
            }
        }
        else if (hasPrefix(ucs2, *len, dia, 3))
        {
            if (decompose)
            {
                splice(ucs2, len, bufferCapacity, 3, 0, (UCS2[]){SPACE,HYPHEN,SPACE}, 3);
                
                if (vf->tense == AORIST && vf->mood == INDICATIVE)
                {
                    splice(ucs2, len, bufferCapacity, 6, 0, (UCS2[]){DECOMPOSED_AUGMENT_CHAR,SPACE,HYPHEN,SPACE}, 4);
                }
            }
            
            ucs2[2] = GREEK_SMALL_LETTER_ALPHA;
        }
        else if (hasPrefix(ucs2, *len, apw, 3))
        {
            if (decompose)
            {
                splice(ucs2, len, bufferCapacity, 2, 0, (UCS2[]){GREEK_SMALL_LETTER_OMICRON,SPACE,HYPHEN,SPACE}, 4);
                
                if (vf->tense == AORIST && vf->mood == INDICATIVE)
                {
                    splice(ucs2, len, bufferCapacity, 6, 1, (UCS2[]){DECOMPOSED_AUGMENT_CHAR,SPACE,HYPHEN,SPACE,GREEK_SMALL_LETTER_OMICRON}, 5);
                }
                else
                {
                    ucs2[6] = GREEK_SMALL_LETTER_OMICRON;
                }
            }
            
            ucs2[2] = GREEK_SMALL_LETTER_OMICRON;
        }
        else if (hasPrefix(ucs2, *len, apo, 3))
        {
            if (decompose)
            {
                splice(ucs2, len, bufferCapacity, 3, 0, (UCS2[]){SPACE,HYPHEN,SPACE}, 3);
                
                if (vf->tense == AORIST && vf->mood == INDICATIVE)
                {
                    splice(ucs2, len, bufferCapacity, 6, 0, (UCS2[]){DECOMPOSED_AUGMENT_CHAR,SPACE,HYPHEN,SPACE}, 4);
                }
            }
            
            ucs2[2] = GREEK_SMALL_LETTER_OMICRON;
        }
        else if (hasPrefix(ucs2, *len, aph, 2))
        {
            if (decompose)
            {
                splice(ucs2, len, bufferCapacity, 1, 1, (UCS2[]){GREEK_SMALL_LETTER_PI,GREEK_SMALL_LETTER_OMICRON,SPACE,HYPHEN,SPACE}, 5);
                
                if (vf->tense == AORIST && vf->mood == INDICATIVE && !(ucs2[6] == GREEK_SMALL_LETTER_ETA && ucs2[7] == GREEK_SMALL_LETTER_KAPPA && (vf->number == SINGULAR || vf->voice != ACTIVE)))
                {
                    splice(ucs2, len, bufferCapacity, 6, 0, (UCS2[]){DECOMPOSED_AUGMENT_CHAR,SPACE,HYPHEN,SPACE}, 4);
                    if (ucs2[10] == GREEK_SMALL_LETTER_EPSILON && ucs2[11] == GREEK_SMALL_LETTER_IOTA)
                    {
                        splice(ucs2, len, bufferCapacity, 10, 2, (UCS2[]){GREEK_SMALL_LETTER_EPSILON_WITH_DASIA}, 1);
                    }
                    else if (ucs2[10] == GREEK_SMALL_LETTER_IOTA && ucs2[11] == COMBINING_MACRON)
                    {//ikneomai
                        splice(ucs2, len, bufferCapacity, 10, 2, (UCS2[]){GREEK_SMALL_LETTER_IOTA_WITH_DASIA}, 1);
                    }
                }
                else if (ucs2[6] == GREEK_SMALL_LETTER_EPSILON && ucs2[7] == GREEK_SMALL_LETTER_IOTA)
                {
                    splice(ucs2, len, bufferCapacity, 6, 2, (UCS2[]){GREEK_SMALL_LETTER_EPSILON_WITH_DASIA}, 1);
                }
                else if (ucs2[6] == GREEK_SMALL_LETTER_IOTA && ucs2[7] == COMBINING_MACRON)
                {   //ikneomai

                    splice(ucs2, len, bufferCapacity, 6, 2, (UCS2[]){GREEK_SMALL_LETTER_IOTA_WITH_DASIA}, 1);
                }
                else if (!(ucs2[6] == GREEK_SMALL_LETTER_ETA && ucs2[7] == GREEK_SMALL_LETTER_KAPPA))
                {
                    splice(ucs2, len, bufferCapacity, 6, 1, NULL, 0);
                }
            }
            else
            {
                if (ucs2[2] == GREEK_SMALL_LETTER_EPSILON && ucs2[3] == GREEK_SMALL_LETTER_IOTA)
                {
                    splice(ucs2, len, bufferCapacity, 3, 1, NULL, 0);
                }
                else if (ucs2[2] == GREEK_SMALL_LETTER_IOTA && ucs2[3] == COMBINING_MACRON)
                {   //ikneomai
                    splice(ucs2, len, bufferCapacity, 3, 1, NULL, 0);
                }
            }
        }
        else if (hasPrefix(ucs2, *len, kath, 3))
        {
            if (decompose)
            {
                splice(ucs2, len, bufferCapacity, 2, 1, (UCS2[]){GREEK_SMALL_LETTER_TAU,GREEK_SMALL_LETTER_ALPHA,SPACE,HYPHEN,SPACE}, 5);
                
                if (vf->tense == AORIST && vf->mood == INDICATIVE)
                {
                    splice(ucs2, len, bufferCapacity, 7, 0, (UCS2[]){DECOMPOSED_AUGMENT_CHAR,SPACE,HYPHEN,SPACE}, 4);
                }
            }
        }
        else if (hasPrefix(ucs2, *len, kate, 4))
        {
            if (decompose)
            {
                splice(ucs2, len, bufferCapacity, 3, 1, (UCS2[]){GREEK_SMALL_LETTER_ALPHA,SPACE,HYPHEN,SPACE}, 4);
                
                if (vf->tense == AORIST && vf->mood == INDICATIVE)
                {
                    splice(ucs2, len, bufferCapacity, 7, 0, (UCS2[]){DECOMPOSED_AUGMENT_CHAR,SPACE,HYPHEN,SPACE}, 4);
                }
            }
            else
            {
                ucs2[3] = GREEK_SMALL_LETTER_ALPHA;
            }
        }
        else if (hasPrefix(ucs2, *len, metan, 5))
        {
            if (decompose)
            {
                splice(ucs2, len, bufferCapacity, 3, 3, (UCS2[]){GREEK_SMALL_LETTER_ALPHA,SPACE,HYPHEN,SPACE,GREEK_SMALL_LETTER_ALPHA,GREEK_SMALL_LETTER_NU,GREEK_SMALL_LETTER_ALPHA,SPACE,HYPHEN,SPACE}, 10);
                
                if (vf->tense == AORIST && vf->mood == INDICATIVE)
                {
                    splice(ucs2, len, bufferCapacity, 13, 0, (UCS2[]){DECOMPOSED_AUGMENT_CHAR,SPACE,HYPHEN,SPACE}, 4);
                    if (ucs2[17] == GREEK_SMALL_LETTER_IOTA)
                    {
                        ucs2[17] = GREEK_SMALL_LETTER_IOTA_WITH_DASIA;
                    }
                }
                else
                {
                    if (ucs2[13] == GREEK_SMALL_LETTER_IOTA)
                    {
                        ucs2[13] = GREEK_SMALL_LETTER_IOTA_WITH_DASIA;
                    }
                }
            }
            else
            {
                ucs2[5] = GREEK_SMALL_LETTER_ALPHA;
            }
        }
        else if (hasPrefix(ucs2, *len, epan, 4))
        {
            if (decompose)
            {
                splice(ucs2, len, bufferCapacity, 2, 3, (UCS2[]){GREEK_SMALL_LETTER_IOTA,SPACE,HYPHEN,SPACE,GREEK_SMALL_LETTER_ALPHA,GREEK_SMALL_LETTER_NU,GREEK_SMALL_LETTER_ALPHA,SPACE,HYPHEN,SPACE}, 10);
                
                if (vf->tense == AORIST && vf->mood == INDICATIVE)
                {
                    splice(ucs2, len, bufferCapacity, 12, 0, (UCS2[]){DECOMPOSED_AUGMENT_CHAR,SPACE,HYPHEN,SPACE}, 4);
                    if (ucs2[16] == GREEK_SMALL_LETTER_IOTA)
                    {
                        ucs2[16] = GREEK_SMALL_LETTER_IOTA_WITH_DASIA;
                    }
                }
                else
                {
                    if (ucs2[12] == GREEK_SMALL_LETTER_IOTA)
                    {
                        ucs2[12] = GREEK_SMALL_LETTER_IOTA_WITH_DASIA;
                    }
                }
            }
            else
            {
                ucs2[4] = GREEK_SMALL_LETTER_ALPHA;
            }
        }
        else if (hasPrefix(ucs2, *len, ep, 2))
        {
            if (decompose)
            {
                splice(ucs2, len, bufferCapacity, 2, 1, (UCS2[]){GREEK_SMALL_LETTER_IOTA,SPACE,HYPHEN,SPACE}, 4);
                
                if (vf->tense == AORIST && vf->mood == INDICATIVE)
                {
                    splice(ucs2, len, bufferCapacity, 6, 0, (UCS2[]){DECOMPOSED_AUGMENT_CHAR,SPACE,HYPHEN,SPACE}, 4);
                    if (ucs2[10] == GREEK_SMALL_LETTER_IOTA)
                    {
                        ucs2[10] = GREEK_SMALL_LETTER_IOTA_WITH_DASIA;
                    }
                }
                else
                {
                    if (ucs2[6] == GREEK_SMALL_LETTER_IOTA)
                    {
                        ucs2[6] = GREEK_SMALL_LETTER_IOTA_WITH_DASIA;
                    }
                }
            }
            else
            {
                ucs2[2] = GREEK_SMALL_LETTER_IOTA;
            }
        }
        else if (hasPrefix(ucs2, *len, meta, 4))
        {
            if (decompose)
            {
                splice(ucs2, len, bufferCapacity, 4, 0, (UCS2[]){SPACE,HYPHEN,SPACE}, 3);
                
                if (vf->tense == AORIST && vf->mood == INDICATIVE)
                {
                    splice(ucs2, len, bufferCapacity, 7, 0, (UCS2[]){DECOMPOSED_AUGMENT_CHAR,SPACE,HYPHEN,SPACE}, 4);
                }
            }
            else
            {
                ucs2[3] = GREEK_SMALL_LETTER_ALPHA;
            }
        }
        else if (hasPrefix(ucs2, *len, mete, 4))
        {
            if (decompose)
            {
                splice(ucs2, len, bufferCapacity, 3, 1, (UCS2[]){GREEK_SMALL_LETTER_ALPHA,SPACE,HYPHEN,SPACE}, 4);
                
                if (vf->tense == AORIST && vf->mood == INDICATIVE)
                {
                    splice(ucs2, len, bufferCapacity, 7, 0, (UCS2[]){DECOMPOSED_AUGMENT_CHAR,SPACE,HYPHEN,SPACE}, 4);
                }
            }
            else
            {
                ucs2[3] = GREEK_SMALL_LETTER_ALPHA;
            }
        }
    }
    else if (vf->tense == AORIST)//removing this because of decompose option.  we already check these things before this is called. && (mood == SUBJUNCTIVE || mood == OPTATIVE || mood == IMPERATIVE))
    {
        if (ucs2[0] == '-')
        {
            if (ucs2[1] == GREEK_SMALL_LETTER_EPSILON && ucs2[2] == GREEK_SMALL_LETTER_IOTA_WITH_DASIA) //ei(
            {
                splice(ucs2, len, bufferCapacity, 1, 2, (UCS2[]){GREEK_SMALL_LETTER_EPSILON_WITH_DASIA}, 1);
            }
            else if (ucs2[1] != GREEK_SMALL_LETTER_ETA_WITH_DASIA)
            {
                splice(ucs2, len, bufferCapacity, 1, 1, NULL, 0);
            }
        }
        else if (ucs2[0] == GREEK_SMALL_LETTER_EPSILON && ucs2[1] == GREEK_SMALL_LETTER_IOTA_WITH_DASIA) //ei(
        {
            splice(ucs2, len, bufferCapacity, 0, 2, (UCS2[]){GREEK_SMALL_LETTER_EPSILON_WITH_DASIA}, 1);
        }
        else if (ucs2[0] == GREEK_SMALL_LETTER_EPSILON && ucs2[1] == GREEK_SMALL_LETTER_IOTA_WITH_PSILI && utf8HasSuffix(vf->verb->aorist, "εἶδον")) //ei)
        {
            splice(ucs2, len, bufferCapacity, 0, 1, NULL, 0);
        }
        else if (hasPrefix(ucs2, *len, err, 3)) //err
        {
            splice(ucs2, len, bufferCapacity, 0, 3, (UCS2[]){GREEK_SMALL_LETTER_RHO_WITH_DASIA}, 1);
        }
        else if (ucs2[0] == GREEK_SMALL_LETTER_EPSILON_WITH_PSILI || ucs2[0] == GREEK_SMALL_LETTER_EPSILON_WITH_DASIA) //strip
        {
            //NSLog(@"removed augment");
            splice(ucs2, len, bufferCapacity, 0, 1, NULL, 0);
        }
        else if (ucs2[0] == GREEK_SMALL_LETTER_ETA && ucs2[1] == GREEK_SMALL_LETTER_UPSILON_WITH_DASIA) //hu)
        {
            ucs2[0] = GREEK_SMALL_LETTER_EPSILON;
        }
        else if (ucs2[0] == GREEK_SMALL_LETTER_ETA_WITH_PSILI )
        {
            if (presentStemInitial == GREEK_SMALL_LETTER_ALPHA_WITH_PSILI)
                ucs2[0] = GREEK_SMALL_LETTER_ALPHA_WITH_PSILI;
            else if (presentStemInitial == GREEK_SMALL_LETTER_EPSILON_WITH_PSILI)
                ucs2[0] = GREEK_SMALL_LETTER_EPSILON_WITH_PSILI;
            else if (presentStemInitial == GREEK_SMALL_LETTER_PHI)//for phero
                ucs2[0] = GREEK_SMALL_LETTER_EPSILON_WITH_PSILI;
            else
                ucs2[0] = GREEK_SMALL_LETTER_EPSILON_WITH_PSILI; //for erhsomai, doesn't have present to check
        }
        else if (ucs2[0] == GREEK_SMALL_LETTER_ETA_WITH_DASIA )
        {
            if (presentStemInitial == GREEK_SMALL_LETTER_ALPHA_WITH_DASIA)
                ucs2[0] = GREEK_SMALL_LETTER_ALPHA_WITH_DASIA;
            else if (presentStemInitial == GREEK_SMALL_LETTER_EPSILON_WITH_DASIA)
                ucs2[0] = GREEK_SMALL_LETTER_EPSILON_WITH_DASIA;
            else if (presentStemInitial == GREEK_SMALL_LETTER_PHI)//for phero
                ucs2[0] = GREEK_SMALL_LETTER_EPSILON_WITH_DASIA;
        }
        else if (ucs2[0] == GREEK_SMALL_LETTER_ETA_WITH_DASIA_AND_YPOGEGRAMMENI) //hi(
        {
            splice(ucs2, len, bufferCapacity, 0, 1, (UCS2[]){GREEK_SMALL_LETTER_ALPHA,GREEK_SMALL_LETTER_IOTA_WITH_DASIA}, 2);
        }
        else if (ucs2[0] == GREEK_SMALL_LETTER_ETA_WITH_PSILI_AND_YPOGEGRAMMENI) //hi)
        {
            splice(ucs2, len, bufferCapacity, 0, 1, (UCS2[]){GREEK_SMALL_LETTER_ALPHA,GREEK_SMALL_LETTER_IOTA_WITH_PSILI}, 2);
        }
        else if (ucs2[0] == GREEK_SMALL_LETTER_OMEGA_WITH_PSILI)
        {
            ucs2[0] = GREEK_SMALL_LETTER_OMICRON_WITH_PSILI;
        }
        
    }
    else if (vf->tense == FUTURE && vf->voice == PASSIVE)
    {
        if (ucs2[0] == '-')
        {
            if (ucs2[1] == GREEK_SMALL_LETTER_EPSILON && ucs2[2] == GREEK_SMALL_LETTER_IOTA_WITH_DASIA) //ei(
            {
                splice(ucs2, len, bufferCapacity, 1, 2, (UCS2[]){GREEK_SMALL_LETTER_EPSILON_WITH_DASIA}, 1);
            }
            else
            {
                splice(ucs2, len, bufferCapacity, 1, 1, NULL, 0);
            }
        }
        else if (ucs2[0] == GREEK_SMALL_LETTER_EPSILON && ucs2[1] == GREEK_SMALL_LETTER_IOTA_WITH_DASIA)
        {
            splice(ucs2, len, bufferCapacity, 0, 2, (UCS2[]){GREEK_SMALL_LETTER_EPSILON_WITH_DASIA}, 1);
        }
        else if (hasPrefix(ucs2, *len, err, 3)) //err
        {
            splice(ucs2, len, bufferCapacity, 0, 3, (UCS2[]){GREEK_SMALL_LETTER_RHO_WITH_DASIA}, 1);
        }
        else if (ucs2[0] == GREEK_SMALL_LETTER_EPSILON_WITH_PSILI || ucs2[0] == GREEK_SMALL_LETTER_EPSILON_WITH_DASIA)
        {
            //NSLog(@"removed augment");
            splice(ucs2, len, bufferCapacity, 0, 1, NULL, 0);
        }
        else if (ucs2[0] == GREEK_SMALL_LETTER_ETA && ucs2[1] == GREEK_SMALL_LETTER_UPSILON_WITH_DASIA) //hu)
        {
            ucs2[0] = GREEK_SMALL_LETTER_EPSILON;
        }
        else if (ucs2[0] == GREEK_SMALL_LETTER_ETA_WITH_PSILI )
        {
            if (presentStemInitial == GREEK_SMALL_LETTER_ALPHA_WITH_PSILI)
                ucs2[0] = GREEK_SMALL_LETTER_ALPHA_WITH_PSILI;
            else if (presentStemInitial == GREEK_SMALL_LETTER_EPSILON_WITH_PSILI)
                ucs2[0] = GREEK_SMALL_LETTER_EPSILON_WITH_PSILI;
            else if (presentStemInitial == GREEK_SMALL_LETTER_PHI)//for phero
                ucs2[0] = GREEK_SMALL_LETTER_EPSILON_WITH_PSILI;
        }
        else if (ucs2[0] == GREEK_SMALL_LETTER_ETA_WITH_DASIA )
        {
            if (presentStemInitial == GREEK_SMALL_LETTER_ALPHA_WITH_DASIA)
                ucs2[0] = GREEK_SMALL_LETTER_ALPHA_WITH_DASIA;
            else if (presentStemInitial == GREEK_SMALL_LETTER_EPSILON_WITH_DASIA)
                ucs2[0] = GREEK_SMALL_LETTER_EPSILON_WITH_DASIA;
            else if (presentStemInitial == GREEK_SMALL_LETTER_PHI)//for phero
                ucs2[0] = GREEK_SMALL_LETTER_EPSILON_WITH_DASIA;
        }
        else if (ucs2[0] == GREEK_SMALL_LETTER_ETA_WITH_DASIA_AND_YPOGEGRAMMENI)
        {
            splice(ucs2, len, bufferCapacity, 0, 1, (UCS2[]){GREEK_SMALL_LETTER_ALPHA,GREEK_SMALL_LETTER_IOTA_WITH_DASIA}, 2);
        }
        else if (ucs2[0] == GREEK_SMALL_LETTER_ETA_WITH_PSILI_AND_YPOGEGRAMMENI)
        {
            splice(ucs2, len, bufferCapacity, 0, 1, (UCS2[]){GREEK_SMALL_LETTER_ALPHA,GREEK_SMALL_LETTER_IOTA_WITH_PSILI}, 2);
        }
        else if (ucs2[0] == GREEK_SMALL_LETTER_OMEGA_WITH_PSILI)
        {
            ucs2[0] = GREEK_SMALL_LETTER_OMICRON_WITH_PSILI;
        }
    }
    
    if (vf->tense == AORIST && vf->mood == INDICATIVE && decompose && (vf->verb->verbclass & PREFIXED) != PREFIXED)
    {
        if (ucs2[0] == '-')
        {
            if (utf8HasSuffix(vf->verb->aorist, "-ἧκα") && ((vf->voice == ACTIVE && vf->number == SINGULAR) || vf->voice == MIDDLE))
                return;
            
            splice(ucs2, len, bufferCapacity, 1, 0, (UCS2[]){SPACE,DECOMPOSED_AUGMENT_CHAR,SPACE,HYPHEN,SPACE}, 5);
        }
        else
        {
            if (ucs2[0] == GREEK_SMALL_LETTER_ETA_WITH_DASIA)
                return;
            
            splice(ucs2, len, bufferCapacity, 0, 0, (UCS2[]){DECOMPOSED_AUGMENT_CHAR,SPACE,HYPHEN,SPACE}, 4);
        }
    }
}

void decomposePrefixes(VerbFormC *vf, UCS2 *ucs2, int *len, int bufferCapacity)
{
    UCS2 ek[] = { GREEK_SMALL_LETTER_EPSILON_WITH_PSILI, GREEK_SMALL_LETTER_KAPPA };
    UCS2 ana[] = { GREEK_SMALL_LETTER_ALPHA_WITH_PSILI, GREEK_SMALL_LETTER_NU, GREEK_SMALL_LETTER_ALPHA };
    UCS2 an[] = { GREEK_SMALL_LETTER_ALPHA_WITH_PSILI, GREEK_SMALL_LETTER_NU };
    UCS2 sum[] = { GREEK_SMALL_LETTER_SIGMA, GREEK_SMALL_LETTER_UPSILON, GREEK_SMALL_LETTER_MU };
    UCS2 sun[] = { GREEK_SMALL_LETTER_SIGMA, GREEK_SMALL_LETTER_UPSILON, GREEK_SMALL_LETTER_NU };
    UCS2 dia[] = { GREEK_SMALL_LETTER_DELTA, GREEK_SMALL_LETTER_IOTA, GREEK_SMALL_LETTER_ALPHA };
    UCS2 dio[] = { GREEK_SMALL_LETTER_DELTA, GREEK_SMALL_LETTER_IOTA, GREEK_SMALL_LETTER_OMICRON }; //fix me hack so this doesn't work on future passive
    UCS2 ape[] = { GREEK_SMALL_LETTER_ALPHA_WITH_PSILI, GREEK_SMALL_LETTER_PI, GREEK_SMALL_LETTER_EPSILON };
    UCS2 apol[] = { GREEK_SMALL_LETTER_ALPHA_WITH_PSILI, GREEK_SMALL_LETTER_PI, GREEK_SMALL_LETTER_OMICRON, GREEK_SMALL_LETTER_LAMDA };
    UCS2 apo[] = { GREEK_SMALL_LETTER_ALPHA_WITH_PSILI, GREEK_SMALL_LETTER_PI, GREEK_SMALL_LETTER_OMICRON };
    UCS2 aph[] = { GREEK_SMALL_LETTER_ALPHA_WITH_PSILI, GREEK_SMALL_LETTER_PHI };
    UCS2 kath[] = { GREEK_SMALL_LETTER_KAPPA, GREEK_SMALL_LETTER_ALPHA, GREEK_SMALL_LETTER_THETA };
    UCS2 kata[] = { GREEK_SMALL_LETTER_KAPPA, GREEK_SMALL_LETTER_ALPHA, GREEK_SMALL_LETTER_TAU, GREEK_SMALL_LETTER_ALPHA };
    UCS2 meta[] = { GREEK_SMALL_LETTER_MU, GREEK_SMALL_LETTER_EPSILON, GREEK_SMALL_LETTER_TAU, GREEK_SMALL_LETTER_ALPHA };
    UCS2 metan[] = { GREEK_SMALL_LETTER_MU, GREEK_SMALL_LETTER_EPSILON, GREEK_SMALL_LETTER_TAU, GREEK_SMALL_LETTER_ALPHA, GREEK_SMALL_LETTER_NU };
    //UCS2 metana[] = { GREEK_SMALL_LETTER_MU, GREEK_SMALL_LETTER_EPSILON, GREEK_SMALL_LETTER_TAU, GREEK_SMALL_LETTER_ALPHA, GREEK_SMALL_LETTER_NU, GREEK_SMALL_LETTER_ALPHA };
    UCS2 epan[] = { GREEK_SMALL_LETTER_EPSILON_WITH_PSILI, GREEK_SMALL_LETTER_PI, GREEK_SMALL_LETTER_ALPHA, GREEK_SMALL_LETTER_NU };
    UCS2 epi[] = { GREEK_SMALL_LETTER_EPSILON_WITH_PSILI, GREEK_SMALL_LETTER_PI, GREEK_SMALL_LETTER_IOTA };
    UCS2 pro[] = { GREEK_SMALL_LETTER_PI, GREEK_SMALL_LETTER_RHO, GREEK_SMALL_LETTER_OMICRON };
    UCS2 para[] = { GREEK_SMALL_LETTER_PI, GREEK_SMALL_LETTER_ALPHA, GREEK_SMALL_LETTER_RHO, GREEK_SMALL_LETTER_ALPHA };
    UCS2 upo[] = { GREEK_SMALL_LETTER_UPSILON_WITH_DASIA, GREEK_SMALL_LETTER_PI,GREEK_SMALL_LETTER_OMICRON };
    UCS2 up[] = { GREEK_SMALL_LETTER_UPSILON_WITH_DASIA, GREEK_SMALL_LETTER_PI };
    
    if (hasPrefix(ucs2, *len, upo, 3))
    {
        splice(ucs2, len, bufferCapacity, 3, 0, (UCS2[]){SPACE,HYPHEN,SPACE}, 3);
    }
    else if (hasPrefix(ucs2, *len, up, 2))
    {
        splice(ucs2, len, bufferCapacity, 2, 0, (UCS2[]){GREEK_SMALL_LETTER_OMICRON, SPACE,HYPHEN,SPACE}, 4);
    }
    else if (hasPrefix(ucs2, *len, para, 4))
    {
        splice(ucs2, len, bufferCapacity, 4, 0, (UCS2[]){SPACE,HYPHEN,SPACE}, 3);
    }
    else if (hasPrefix(ucs2, *len, ek, 2))
    {
        splice(ucs2, len, bufferCapacity, 2, 0, (UCS2[]){SPACE,HYPHEN,SPACE}, 3);
    }
    else if (hasPrefix(ucs2, *len, pro, 3))
    {
        splice(ucs2, len, bufferCapacity, 3, 0, (UCS2[]){SPACE,HYPHEN,SPACE}, 3);
    }
    else if (hasPrefix(ucs2, *len, ana, 3))
    {
        splice(ucs2, len, bufferCapacity, 3, 0, (UCS2[]){SPACE,HYPHEN,SPACE}, 3);
    }
    else if (hasPrefix(ucs2, *len, an, 2))
    {
        splice(ucs2, len, bufferCapacity, 2, 0, (UCS2[]){GREEK_SMALL_LETTER_ALPHA,SPACE,HYPHEN,SPACE}, 4);
    }
    else if (hasPrefix(ucs2, *len, sum, 3))
    {
        splice(ucs2, len, bufferCapacity, 2, 1, (UCS2[]){GREEK_SMALL_LETTER_NU,SPACE,HYPHEN,SPACE}, 4);
    }
    else if (hasPrefix(ucs2, *len, sun, 3))
    {
        splice(ucs2, len, bufferCapacity, 2, 1, (UCS2[]){GREEK_SMALL_LETTER_NU,SPACE,HYPHEN,SPACE}, 4);
        if (ucs2[6] == GREEK_SMALL_LETTER_IOTA && ucs2[7] == COMBINING_MACRON)
        {
            splice(ucs2, len, bufferCapacity, 8, 0, (UCS2[]){COMBINING_ROUGH_BREATHING}, 1);
        }
        else if (ucs2[6] == GREEK_SMALL_LETTER_EPSILON && ucs2[7] == GREEK_SMALL_LETTER_IOTA && ucs2[8] == GREEK_SMALL_LETTER_SIGMA)
        {
            ucs2[7] = GREEK_SMALL_LETTER_IOTA_WITH_PSILI;
        }
        else if (ucs2[6] == GREEK_SMALL_LETTER_EPSILON && ucs2[7] == GREEK_SMALL_LETTER_IOTA)
        {
            ucs2[7] = GREEK_SMALL_LETTER_IOTA_WITH_DASIA;
        }
        else if (vf->tense == FUTURE && vf->voice != PASSIVE && utf8HasSuffix(vf->verb->present, "ῑ́ημι"))
        {
            ucs2[6] = GREEK_SMALL_LETTER_ETA_WITH_DASIA;
        }
    }
    else if (hasPrefix(ucs2, *len, dia, 3))
    {
        splice(ucs2, len, bufferCapacity, 3, 0, (UCS2[]){SPACE,HYPHEN,SPACE}, 3);
    }
    else if (hasPrefix(ucs2, *len, dio, 3))
    {
        splice(ucs2, len, bufferCapacity, 2, 0, (UCS2[]){GREEK_SMALL_LETTER_ALPHA,SPACE,HYPHEN,SPACE}, 4);
    }
    else if (hasPrefix(ucs2, *len, ape, 3) && vf->tense == PERFECT)
    {
        splice(ucs2, len, bufferCapacity, 2, 0, (UCS2[]){GREEK_SMALL_LETTER_OMICRON,SPACE,HYPHEN,SPACE}, 4);
    }
    else if (hasPrefix(ucs2, *len, apol, 4))
    {
        splice(ucs2, len, bufferCapacity, 2, 0, (UCS2[]){GREEK_SMALL_LETTER_OMICRON,SPACE,HYPHEN,SPACE}, 4);
    }
    else if (hasPrefix(ucs2, *len, apo, 3))
    {
        splice(ucs2, len, bufferCapacity, 3, 0, (UCS2[]){SPACE,HYPHEN,SPACE}, 3);
    }
    else if (hasPrefix(ucs2, *len, epi, 3))
    {
        splice(ucs2, len, bufferCapacity, 3, 0, (UCS2[]){SPACE,HYPHEN,SPACE}, 3);
    }
    else if (hasPrefix(ucs2, *len, aph, 2))
    {
        splice(ucs2, len, bufferCapacity, 1, 1, (UCS2[]){GREEK_SMALL_LETTER_PI,GREEK_SMALL_LETTER_OMICRON,SPACE,HYPHEN,SPACE}, 5);
        
        if (vf->tense == FUTURE && vf->voice != PASSIVE && utf8HasSuffix(vf->verb->present, "ῑ́ημι"))
        {
            ucs2[6] = GREEK_SMALL_LETTER_ETA_WITH_DASIA;
        }
        else if (ucs2[6] == GREEK_SMALL_LETTER_IOTA_WITH_PERISPOMENI)
        {
            ucs2[6] = GREEK_SMALL_LETTER_IOTA_WITH_DASIA_AND_PERISPOMENI;
        }
        else if (ucs2[6] == GREEK_SMALL_LETTER_IOTA && ucs2[7] == COMBINING_MACRON)
        {
            splice(ucs2, len, bufferCapacity, 8, 0, (UCS2[]){COMBINING_ROUGH_BREATHING}, 1);
        }
        else if (ucs2[6] == GREEK_SMALL_LETTER_IOTA)
        {
            ucs2[6] = GREEK_SMALL_LETTER_IOTA_WITH_DASIA;
        }
        else if (ucs2[6] == GREEK_SMALL_LETTER_EPSILON && ucs2[7] == GREEK_SMALL_LETTER_IOTA && vf->tense == PERFECT)
        {
            ucs2[7] = GREEK_SMALL_LETTER_IOTA_WITH_DASIA;
        }
        else if (ucs2[6] == GREEK_SMALL_LETTER_EPSILON && ucs2[7] == GREEK_SMALL_LETTER_IOTA)
        {
            splice(ucs2, len, bufferCapacity, 6, 1, (UCS2[]){GREEK_SMALL_LETTER_EPSILON_WITH_DASIA}, 1);
        }
        else if (ucs2[6] == GREEK_SMALL_LETTER_EPSILON)
        {
            ucs2[6] = GREEK_SMALL_LETTER_EPSILON_WITH_DASIA;
        }
    }
    else if (hasPrefix(ucs2, *len, kath, 3))
    {
        splice(ucs2, len, bufferCapacity, 2, 1, (UCS2[]){GREEK_SMALL_LETTER_TAU,GREEK_SMALL_LETTER_ALPHA,SPACE,HYPHEN,SPACE}, 5);
        
        if (ucs2[7] == GREEK_SMALL_LETTER_IOTA)
        {
            ucs2[7] = GREEK_SMALL_LETTER_IOTA_WITH_DASIA;
        }
        else if (ucs2[7] == GREEK_SMALL_LETTER_EPSILON)
        {
            ucs2[7] = GREEK_SMALL_LETTER_EPSILON_WITH_DASIA;
        }
    }
    else if (hasPrefix(ucs2, *len, kata, 4))
    {
        splice(ucs2, len, bufferCapacity, 4, 0, (UCS2[]){SPACE,HYPHEN,SPACE}, 3);
    }
    else if (hasPrefix(ucs2, *len, metan, 5))
    {
        UCS2 firstNonPrefixLetter = ucs2[5];

        splice(ucs2, len, bufferCapacity, 3, 3, (UCS2[]){GREEK_SMALL_LETTER_ALPHA,SPACE,HYPHEN,SPACE,GREEK_SMALL_LETTER_ALPHA,GREEK_SMALL_LETTER_NU,GREEK_SMALL_LETTER_ALPHA,SPACE,HYPHEN,SPACE}, 10);

        if (firstNonPrefixLetter == GREEK_SMALL_LETTER_IOTA)
        {
            splice(ucs2, len, bufferCapacity, 13, 0, (UCS2[]){GREEK_SMALL_LETTER_IOTA_WITH_DASIA}, 1);
        }
        else if (firstNonPrefixLetter == GREEK_SMALL_LETTER_EPSILON)
        {
            splice(ucs2, len, bufferCapacity, 13, 0, (UCS2[]){GREEK_SMALL_LETTER_EPSILON_WITH_DASIA}, 1);
        }
    }
    else if (hasPrefix(ucs2, *len, epan, 4))
    {
        //get letter first
        UCS2 firstNonPrefixLetter = ucs2[4];
        
        splice(ucs2, len, bufferCapacity, 2, 3, (UCS2[]){GREEK_SMALL_LETTER_IOTA,SPACE,HYPHEN,SPACE,GREEK_SMALL_LETTER_ALPHA,GREEK_SMALL_LETTER_NU,GREEK_SMALL_LETTER_ALPHA,SPACE,HYPHEN,SPACE}, 10);
        
        if (firstNonPrefixLetter == GREEK_SMALL_LETTER_IOTA)
        {
            splice(ucs2, len, bufferCapacity, 12, 0, (UCS2[]){GREEK_SMALL_LETTER_IOTA_WITH_DASIA}, 1);
        }
        else if (firstNonPrefixLetter == GREEK_SMALL_LETTER_EPSILON)
        {
            splice(ucs2, len, bufferCapacity, 12, 0, (UCS2[]){GREEK_SMALL_LETTER_EPSILON_WITH_DASIA}, 1);
        }
    }
    else if (hasPrefix(ucs2, *len, meta, 4))
    {
        splice(ucs2, len, bufferCapacity, 4, 0, (UCS2[]){SPACE,HYPHEN,SPACE}, 3);
    }
}
