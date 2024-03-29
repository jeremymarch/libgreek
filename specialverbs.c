//
//  specialverbs.c
//  HopliteChallenge
//
//  Created by Jeremy March on 9/11/18.
//  Copyright © 2018 Jeremy March. All rights reserved.
//
#include <stdbool.h>
#include "specialverbs.h"

int getEsti(VerbFormC *vf, UCS2 *buffer, int *bufferLen, int bufferCapacity)
{
    if ( vf->person == THIRD && vf->number == SINGULAR && vf->mood == INDICATIVE)
    {
        if ( vf->tense == PRESENT && vf->voice == ACTIVE)
        {
            ucsplice(buffer, bufferLen, bufferCapacity, *bufferLen, 0, (UCS2[]){GREEK_SMALL_LETTER_EPSILON_WITH_PSILI_AND_OXIA,GREEK_SMALL_LETTER_SIGMA,GREEK_SMALL_LETTER_TAU,GREEK_SMALL_LETTER_IOTA,LEFT_PARENTHESIS,GREEK_SMALL_LETTER_NU,RIGHT_PARENTHESIS}, 7);
            return 1;
        }
        else if ( vf->tense == IMPERFECT && vf->voice == ACTIVE)
        {
            ucsplice(buffer, bufferLen, bufferCapacity, *bufferLen, 0, (UCS2[]){GREEK_SMALL_LETTER_ETA_WITH_PSILI_AND_PERISPOMENI,GREEK_SMALL_LETTER_NU}, 2);
            return 1;
        }
        else if ( vf->tense == FUTURE && vf->voice == MIDDLE)
        {
            ucsplice(buffer, bufferLen, bufferCapacity, *bufferLen, 0, (UCS2[]){GREEK_SMALL_LETTER_EPSILON_WITH_PSILI_AND_OXIA,GREEK_SMALL_LETTER_SIGMA,GREEK_SMALL_LETTER_TAU, GREEK_SMALL_LETTER_ALPHA,GREEK_SMALL_LETTER_IOTA }, 5);
            return 1;
        }
        else
        {
            return 0;
        }
    }
    else
    {
        return 0;
    }
}

int getExesti(VerbFormC *vf, UCS2 *buffer, int *bufferLen, int bufferCapacity, bool decompose)
{
    if ( vf->person == THIRD && vf->number == SINGULAR && vf->mood == INDICATIVE)
    {
        if ( vf->tense == PRESENT && vf->voice == ACTIVE)
        {
            if (!decompose)
                ucsplice(buffer, bufferLen, bufferCapacity, *bufferLen, 0, (UCS2[]){GREEK_SMALL_LETTER_EPSILON_WITH_PSILI_AND_OXIA,GREEK_SMALL_LETTER_XI,GREEK_SMALL_LETTER_EPSILON,GREEK_SMALL_LETTER_SIGMA,GREEK_SMALL_LETTER_TAU,GREEK_SMALL_LETTER_IOTA,LEFT_PARENTHESIS,GREEK_SMALL_LETTER_NU,RIGHT_PARENTHESIS}, 9);
            else
                ucsplice(buffer, bufferLen, bufferCapacity, *bufferLen, 0, (UCS2[]){GREEK_SMALL_LETTER_EPSILON_WITH_PSILI,GREEK_SMALL_LETTER_XI,SPACE,HYPHEN,SPACE,GREEK_SMALL_LETTER_EPSILON,GREEK_SMALL_LETTER_SIGMA,GREEK_SMALL_LETTER_TAU,GREEK_SMALL_LETTER_IOTA,LEFT_PARENTHESIS,GREEK_SMALL_LETTER_NU,RIGHT_PARENTHESIS}, 12);
                
            return 1;
        }
        else if ( vf->tense == IMPERFECT && vf->voice == ACTIVE)
        {
            if (!decompose)
                ucsplice(buffer, bufferLen, bufferCapacity, *bufferLen, 0, (UCS2[]){GREEK_SMALL_LETTER_EPSILON_WITH_PSILI,GREEK_SMALL_LETTER_XI,GREEK_SMALL_LETTER_ETA_WITH_PERISPOMENI,GREEK_SMALL_LETTER_NU}, 4);
            else
                ucsplice(buffer, bufferLen, bufferCapacity, *bufferLen, 0, (UCS2[]){GREEK_SMALL_LETTER_EPSILON_WITH_PSILI,GREEK_SMALL_LETTER_XI,SPACE,HYPHEN,SPACE,GREEK_SMALL_LETTER_ETA,GREEK_SMALL_LETTER_NU}, 7);
            return 1;
        }
        else if ( vf->tense == FUTURE && vf->voice == MIDDLE)
        {
            if (!decompose)
                ucsplice(buffer, bufferLen, bufferCapacity, *bufferLen, 0, (UCS2[]){GREEK_SMALL_LETTER_EPSILON_WITH_PSILI,GREEK_SMALL_LETTER_XI,EPSILON_WITH_ACUTE,GREEK_SMALL_LETTER_SIGMA,GREEK_SMALL_LETTER_TAU, GREEK_SMALL_LETTER_ALPHA,GREEK_SMALL_LETTER_IOTA }, 7);
            else
                ucsplice(buffer, bufferLen, bufferCapacity, *bufferLen, 0, (UCS2[]){GREEK_SMALL_LETTER_EPSILON_WITH_PSILI,GREEK_SMALL_LETTER_XI,SPACE,HYPHEN,SPACE,GREEK_SMALL_LETTER_EPSILON,GREEK_SMALL_LETTER_SIGMA,GREEK_SMALL_LETTER_EPSILON,GREEK_SMALL_LETTER_TAU, GREEK_SMALL_LETTER_ALPHA,GREEK_SMALL_LETTER_IOTA }, 11);
            return 1;
        }
        else
        {
            return 0;
        }
    }
    else
    {
        return 0;
    }
}

int getEimi(VerbFormC *vf, UCS2 *buffer, int *bufferLen, int bufferCapacity)
{
    //only present/imperfect active for eimi/
    if ( (vf->tense == PRESENT || vf->tense == IMPERFECT) && vf->voice != ACTIVE )
    {
        return 0;
    }
    if (vf->tense == PRESENT)
    {
        if (vf->mood == INDICATIVE)
        {
            if (vf->person == FIRST && vf->number == SINGULAR)
            {
                ucsplice(buffer, bufferLen, bufferCapacity, *bufferLen, 0, (UCS2[]){GREEK_SMALL_LETTER_EPSILON,GREEK_SMALL_LETTER_IOTA_WITH_PSILI,GREEK_SMALL_LETTER_MU,IOTA_WITH_ACUTE}, 4);
            }
            else if (vf->person == SECOND && vf->number == SINGULAR)
            {
                ucsplice(buffer, bufferLen, bufferCapacity, *bufferLen, 0, (UCS2[]){GREEK_SMALL_LETTER_EPSILON,GREEK_SMALL_LETTER_IOTA_WITH_PSILI_AND_PERISPOMENI}, 2);
            }
            else if (vf->person == THIRD && vf->number == SINGULAR)
            {
                ucsplice(buffer, bufferLen, bufferCapacity, *bufferLen, 0, (UCS2[]){GREEK_SMALL_LETTER_EPSILON_WITH_PSILI,GREEK_SMALL_LETTER_SIGMA,GREEK_SMALL_LETTER_TAU,IOTA_WITH_ACUTE,LEFT_PARENTHESIS, GREEK_SMALL_LETTER_NU,RIGHT_PARENTHESIS}, 7);
            }
            else if (vf->person == FIRST && vf->number == PLURAL)
            {
                ucsplice(buffer, bufferLen, bufferCapacity, *bufferLen, 0, (UCS2[]){GREEK_SMALL_LETTER_EPSILON_WITH_PSILI,GREEK_SMALL_LETTER_SIGMA,GREEK_SMALL_LETTER_MU,EPSILON_WITH_ACUTE,GREEK_SMALL_LETTER_NU}, 5);
            }
            else if (vf->person == SECOND && vf->number == PLURAL)
            {
                ucsplice(buffer, bufferLen, bufferCapacity, *bufferLen, 0, (UCS2[]){GREEK_SMALL_LETTER_EPSILON_WITH_PSILI,GREEK_SMALL_LETTER_SIGMA,GREEK_SMALL_LETTER_TAU,EPSILON_WITH_ACUTE}, 4);
            }
            else if (vf->person == THIRD && vf->number == PLURAL)
            {
                ucsplice(buffer, bufferLen, bufferCapacity, *bufferLen, 0, (UCS2[]){GREEK_SMALL_LETTER_EPSILON,GREEK_SMALL_LETTER_IOTA_WITH_PSILI, GREEK_SMALL_LETTER_SIGMA,IOTA_WITH_ACUTE,LEFT_PARENTHESIS, GREEK_SMALL_LETTER_NU,RIGHT_PARENTHESIS}, 7);
            }
        }
        else if (vf->mood == SUBJUNCTIVE)
        {
            if (vf->person == FIRST && vf->number == SINGULAR)
            {
                ucsplice(buffer, bufferLen, bufferCapacity, *bufferLen, 0, (UCS2[]){GREEK_SMALL_LETTER_OMEGA_WITH_PSILI_AND_PERISPOMENI}, 1);
            }
            else if (vf->person == SECOND && vf->number == SINGULAR)
            {
                ucsplice(buffer, bufferLen, bufferCapacity, *bufferLen, 0, (UCS2[]){GREEK_SMALL_LETTER_ETA_WITH_PSILI_AND_PERISPOMENI_AND_YPOGEGRAMMENI,GREEK_SMALL_LETTER_FINAL_SIGMA}, 2);
            }
            else if (vf->person == THIRD && vf->number == SINGULAR)
            {
                ucsplice(buffer, bufferLen, bufferCapacity, *bufferLen, 0, (UCS2[]){GREEK_SMALL_LETTER_ETA_WITH_PSILI_AND_PERISPOMENI_AND_YPOGEGRAMMENI}, 1);
            }
            else if (vf->person == FIRST && vf->number == PLURAL)
            {
                ucsplice(buffer, bufferLen, bufferCapacity, *bufferLen, 0, (UCS2[]){GREEK_SMALL_LETTER_OMEGA_WITH_PSILI_AND_PERISPOMENI,GREEK_SMALL_LETTER_MU,GREEK_SMALL_LETTER_EPSILON,GREEK_SMALL_LETTER_NU}, 4);
            }
            else if (vf->person == SECOND && vf->number == PLURAL)
            {
                ucsplice(buffer, bufferLen, bufferCapacity, *bufferLen, 0, (UCS2[]){GREEK_SMALL_LETTER_ETA_WITH_PSILI_AND_PERISPOMENI,GREEK_SMALL_LETTER_TAU,GREEK_SMALL_LETTER_EPSILON}, 3);
            }
            else if (vf->person == THIRD && vf->number == PLURAL)
            {
                ucsplice(buffer, bufferLen, bufferCapacity, *bufferLen, 0, (UCS2[]){GREEK_SMALL_LETTER_OMEGA_WITH_PSILI_AND_PERISPOMENI,GREEK_SMALL_LETTER_SIGMA,GREEK_SMALL_LETTER_IOTA,LEFT_PARENTHESIS,GREEK_SMALL_LETTER_NU,RIGHT_PARENTHESIS}, 6);
            }
        }
        else if (vf->mood == OPTATIVE)
        {
            if (vf->person == FIRST && vf->number == SINGULAR)
            {
                ucsplice(buffer, bufferLen, bufferCapacity, *bufferLen, 0, (UCS2[]){GREEK_SMALL_LETTER_EPSILON,GREEK_SMALL_LETTER_IOTA_WITH_PSILI_AND_OXIA,GREEK_SMALL_LETTER_ETA,GREEK_SMALL_LETTER_NU}, 4);
            }
            else if (vf->person == SECOND && vf->number == SINGULAR)
            {
                ucsplice(buffer, bufferLen, bufferCapacity, *bufferLen, 0, (UCS2[]){GREEK_SMALL_LETTER_EPSILON,GREEK_SMALL_LETTER_IOTA_WITH_PSILI_AND_OXIA,GREEK_SMALL_LETTER_ETA,GREEK_SMALL_LETTER_FINAL_SIGMA}, 4);
            }
            else if (vf->person == THIRD && vf->number == SINGULAR)
            {
                ucsplice(buffer, bufferLen, bufferCapacity, *bufferLen, 0, (UCS2[]){GREEK_SMALL_LETTER_EPSILON,GREEK_SMALL_LETTER_IOTA_WITH_PSILI_AND_OXIA,GREEK_SMALL_LETTER_ETA}, 3);
            }
            else if (vf->person == FIRST && vf->number == PLURAL)
            {
                ucsplice(buffer, bufferLen, bufferCapacity, *bufferLen, 0, (UCS2[]){GREEK_SMALL_LETTER_EPSILON,GREEK_SMALL_LETTER_IOTA_WITH_PSILI_AND_PERISPOMENI, GREEK_SMALL_LETTER_MU,GREEK_SMALL_LETTER_EPSILON,GREEK_SMALL_LETTER_NU,COMMA,SPACE,GREEK_SMALL_LETTER_EPSILON,GREEK_SMALL_LETTER_IOTA_WITH_PSILI_AND_OXIA,GREEK_SMALL_LETTER_ETA,GREEK_SMALL_LETTER_MU,GREEK_SMALL_LETTER_EPSILON, GREEK_SMALL_LETTER_NU}, 13);
            }
            else if (vf->person == SECOND && vf->number == PLURAL)
            {
                ucsplice(buffer, bufferLen, bufferCapacity, *bufferLen, 0, (UCS2[]){GREEK_SMALL_LETTER_EPSILON,GREEK_SMALL_LETTER_IOTA_WITH_PSILI_AND_PERISPOMENI, GREEK_SMALL_LETTER_TAU,GREEK_SMALL_LETTER_EPSILON,COMMA,SPACE,GREEK_SMALL_LETTER_EPSILON,GREEK_SMALL_LETTER_IOTA_WITH_PSILI_AND_OXIA,GREEK_SMALL_LETTER_ETA,GREEK_SMALL_LETTER_TAU,GREEK_SMALL_LETTER_EPSILON}, 11);
            }
            else if (vf->person == THIRD && vf->number == PLURAL)
            {
                ucsplice(buffer, bufferLen, bufferCapacity, *bufferLen, 0, (UCS2[]){GREEK_SMALL_LETTER_EPSILON,GREEK_SMALL_LETTER_IOTA_WITH_PSILI_AND_PERISPOMENI, GREEK_SMALL_LETTER_EPSILON,GREEK_SMALL_LETTER_NU,COMMA,SPACE,GREEK_SMALL_LETTER_EPSILON,GREEK_SMALL_LETTER_IOTA_WITH_PSILI_AND_OXIA,GREEK_SMALL_LETTER_ETA,GREEK_SMALL_LETTER_SIGMA,GREEK_SMALL_LETTER_ALPHA,GREEK_SMALL_LETTER_NU}, 12);
            }
        }
        else if (vf->mood == IMPERATIVE)
        {
            if (vf->person == FIRST && vf->number == SINGULAR)
            {
                return 0;
            }
            else if (vf->person == SECOND && vf->number == SINGULAR)
            {
                ucsplice(buffer, bufferLen, bufferCapacity, *bufferLen, 0, (UCS2[]){GREEK_SMALL_LETTER_IOTA_WITH_PSILI_AND_OXIA,GREEK_SMALL_LETTER_SIGMA,GREEK_SMALL_LETTER_THETA,GREEK_SMALL_LETTER_IOTA}, 4);
            }
            else if (vf->person == THIRD && vf->number == SINGULAR)
            {
                ucsplice(buffer, bufferLen, bufferCapacity, *bufferLen, 0, (UCS2[]){GREEK_SMALL_LETTER_EPSILON_WITH_PSILI_AND_OXIA,GREEK_SMALL_LETTER_SIGMA,GREEK_SMALL_LETTER_TAU,GREEK_SMALL_LETTER_OMEGA}, 4);
            }
            else if (vf->person == FIRST && vf->number == PLURAL)
            {
                return 0;
            }
            else if (vf->person == SECOND && vf->number == PLURAL)
            {
                ucsplice(buffer, bufferLen, bufferCapacity, *bufferLen, 0, (UCS2[]){GREEK_SMALL_LETTER_EPSILON_WITH_PSILI_AND_OXIA,GREEK_SMALL_LETTER_SIGMA,GREEK_SMALL_LETTER_TAU,GREEK_SMALL_LETTER_EPSILON}, 4);
            }
            else if (vf->person == THIRD && vf->number == PLURAL)
            {
                ucsplice(buffer, bufferLen, bufferCapacity, *bufferLen, 0, (UCS2[]){GREEK_SMALL_LETTER_EPSILON_WITH_PSILI_AND_OXIA,GREEK_SMALL_LETTER_SIGMA, GREEK_SMALL_LETTER_TAU,GREEK_SMALL_LETTER_OMEGA,GREEK_SMALL_LETTER_NU,COMMA,SPACE,GREEK_SMALL_LETTER_OMICRON_WITH_PSILI_AND_OXIA,GREEK_SMALL_LETTER_NU,GREEK_SMALL_LETTER_TAU,GREEK_SMALL_LETTER_OMEGA,GREEK_SMALL_LETTER_NU}, 12);
            }
        }
    }
    else if (vf->tense == IMPERFECT)
    {
        if (vf->person == FIRST && vf->number == SINGULAR)
        {
            ucsplice(buffer, bufferLen, bufferCapacity, *bufferLen, 0, (UCS2[]){GREEK_SMALL_LETTER_ETA_WITH_PSILI_AND_PERISPOMENI,COMMA,SPACE,GREEK_SMALL_LETTER_ETA_WITH_PSILI_AND_PERISPOMENI,GREEK_SMALL_LETTER_NU}, 5);
        }
        else if (vf->person == SECOND && vf->number == SINGULAR)
        {
            ucsplice(buffer, bufferLen, bufferCapacity, *bufferLen, 0, (UCS2[]){GREEK_SMALL_LETTER_ETA_WITH_PSILI_AND_PERISPOMENI,GREEK_SMALL_LETTER_SIGMA,GREEK_SMALL_LETTER_THETA,GREEK_SMALL_LETTER_ALPHA}, 4);
        }
        else if (vf->person == THIRD && vf->number == SINGULAR)
        {
            ucsplice(buffer, bufferLen, bufferCapacity, *bufferLen, 0, (UCS2[]){GREEK_SMALL_LETTER_ETA_WITH_PSILI_AND_PERISPOMENI,GREEK_SMALL_LETTER_NU}, 2);
        }
        else if (vf->person == FIRST && vf->number == PLURAL)
        {
            ucsplice(buffer, bufferLen, bufferCapacity, *bufferLen, 0, (UCS2[]){GREEK_SMALL_LETTER_ETA_WITH_PSILI_AND_PERISPOMENI,GREEK_SMALL_LETTER_MU,GREEK_SMALL_LETTER_EPSILON,GREEK_SMALL_LETTER_NU}, 4);
        }
        else if (vf->person == SECOND && vf->number == PLURAL)
        {
            ucsplice(buffer, bufferLen, bufferCapacity, *bufferLen, 0, (UCS2[]){GREEK_SMALL_LETTER_ETA_WITH_PSILI_AND_PERISPOMENI,GREEK_SMALL_LETTER_TAU,GREEK_SMALL_LETTER_EPSILON}, 3);
        }
        else if (vf->person == THIRD && vf->number == PLURAL)
        {
            ucsplice(buffer, bufferLen, bufferCapacity, *bufferLen, 0, (UCS2[]){GREEK_SMALL_LETTER_ETA_WITH_PSILI_AND_PERISPOMENI,GREEK_SMALL_LETTER_SIGMA,GREEK_SMALL_LETTER_ALPHA,GREEK_SMALL_LETTER_NU}, 4);
        }
    }
    else
    {
        return 0;
    }
    return 1;
}

int getDei(VerbFormC *vf, UCS2 *buffer, int *bufferLen, int bufferCapacity, bool decompose)
{
    if (vf->person == THIRD && vf->number == SINGULAR && vf->voice == ACTIVE)
    {
        ucsplice(buffer, bufferLen, bufferCapacity, *bufferLen, 0, (UCS2[]){GREEK_SMALL_LETTER_DELTA,GREEK_SMALL_LETTER_EPSILON}, 2);
        if (decompose)
        {
            ucsplice(buffer, bufferLen, bufferCapacity, *bufferLen, 0, (UCS2[]){SPACE,HYPHEN,SPACE}, 3);
        }
        if (vf->tense == PRESENT)
        {
            if (vf->mood == INDICATIVE)
            {
                if (decompose)
                {
                    ucsplice(buffer, bufferLen, bufferCapacity, *bufferLen, 0, (UCS2[]){GREEK_SMALL_LETTER_EPSILON,GREEK_SMALL_LETTER_IOTA_WITH_PERISPOMENI}, 2);
                }
                else
                {
                    ucsplice(buffer, bufferLen, bufferCapacity, *bufferLen, 0, (UCS2[]){GREEK_SMALL_LETTER_IOTA_WITH_PERISPOMENI}, 1);
                }
            }
            else if (vf->mood == SUBJUNCTIVE)
            {
                ucsplice(buffer, bufferLen, bufferCapacity, *bufferLen, 0, (UCS2[]){GREEK_SMALL_LETTER_ETA_WITH_YPOGEGRAMMENI}, 1);
            }
            else if (vf->mood == OPTATIVE)
            {
                ucsplice(buffer, bufferLen, bufferCapacity, *bufferLen, 0, (UCS2[]){GREEK_SMALL_LETTER_OMICRON,GREEK_SMALL_LETTER_IOTA}, 2);
            }
            else
            {
                return 0;
            }
        }
        else if (vf->tense == IMPERFECT && vf->mood == INDICATIVE)
        {
            if (decompose)
                ucsplice(buffer, bufferLen, bufferCapacity, 0, 0, (UCS2[]){GREEK_SMALL_LETTER_EPSILON}, 1);
            else
                ucsplice(buffer, bufferLen, bufferCapacity, 0, 0, (UCS2[]){GREEK_SMALL_LETTER_EPSILON_WITH_PSILI}, 1);
            
            if (decompose)
            {
                ucsplice(buffer, bufferLen, bufferCapacity, 1, 0, (UCS2[]){SPACE,HYPHEN,SPACE}, 3);
            }
            if (decompose)
                ucsplice(buffer, bufferLen, bufferCapacity, *bufferLen, 0, (UCS2[]){GREEK_SMALL_LETTER_EPSILON}, 1);
            else
                ucsplice(buffer, bufferLen, bufferCapacity, *bufferLen, 0, (UCS2[]){GREEK_SMALL_LETTER_IOTA}, 1);
        }
        else if (vf->tense == FUTURE && vf->mood == INDICATIVE)
        {
            if (decompose)
            {
                ucsplice(buffer, bufferLen, bufferCapacity, 2, 0, (UCS2[]){GREEK_SMALL_LETTER_ETA,GREEK_SMALL_LETTER_SIGMA}, 2);
            }
            else
            {
                ucsplice(buffer, bufferLen, bufferCapacity, *bufferLen, 0, (UCS2[]){GREEK_SMALL_LETTER_ETA,GREEK_SMALL_LETTER_SIGMA}, 2);
            }
            ucsplice(buffer, bufferLen, bufferCapacity, *bufferLen, 0, (UCS2[]){GREEK_SMALL_LETTER_EPSILON,GREEK_SMALL_LETTER_IOTA}, 2);
        }
        else if (vf->tense == FUTURE && vf->mood == OPTATIVE)
        {
            //no future optative: H&Q p 565, 566
            return 0;
        }
        else if (vf->tense == AORIST && vf->mood == INDICATIVE)
        {
            if (decompose)
                ucsplice(buffer, bufferLen, bufferCapacity, 0, 0, (UCS2[]){GREEK_SMALL_LETTER_EPSILON}, 1);
            else
                ucsplice(buffer, bufferLen, bufferCapacity, 0, 0, (UCS2[]){GREEK_SMALL_LETTER_EPSILON_WITH_PSILI}, 1);
            
            if (decompose)
            {
                ucsplice(buffer, bufferLen, bufferCapacity, 1, 0, (UCS2[]){SPACE,HYPHEN,SPACE}, 3);
                
                ucsplice(buffer, bufferLen, bufferCapacity, 6, 0, (UCS2[]){GREEK_SMALL_LETTER_ETA,GREEK_SMALL_LETTER_SIGMA}, 2);
            }
            else
            {
                ucsplice(buffer, bufferLen, bufferCapacity, *bufferLen, 0, (UCS2[]){GREEK_SMALL_LETTER_ETA,GREEK_SMALL_LETTER_SIGMA}, 2);
            }
            ucsplice(buffer, bufferLen, bufferCapacity, *bufferLen, 0, (UCS2[]){GREEK_SMALL_LETTER_EPSILON,LEFT_PARENTHESIS,GREEK_SMALL_LETTER_NU,RIGHT_PARENTHESIS}, 4);
        }
        else
        {
            return 0;
        }
        return 1;
    }
    else
    {
        return 0;
    }
}

int getXrh(VerbFormC *vf, UCS2 *buffer, int *bufferLen, int bufferCapacity, bool decompose)
{
    if (vf->person == THIRD && vf->number == SINGULAR && vf->voice == ACTIVE)
    {
        ucsplice(buffer, bufferLen, bufferCapacity, 0, 0, (UCS2[]){GREEK_SMALL_LETTER_CHI,GREEK_SMALL_LETTER_RHO,ETA_WITH_ACUTE}, 3);
        if (decompose && !(vf->tense == PRESENT && vf->mood == INDICATIVE))
        {
            ucsplice(buffer, bufferLen, bufferCapacity, *bufferLen, 0, (UCS2[]){SPACE,HYPHEN,SPACE}, 3);
        }
        if (vf->tense == PRESENT)
        {
            if (vf->mood == INDICATIVE)
            {
                
            }
            else if (vf->mood == SUBJUNCTIVE)
            {
                if (!decompose)
                {
                    ucsplice(buffer, bufferLen, bufferCapacity, *bufferLen - 1, 1, (UCS2[]){GREEK_SMALL_LETTER_ETA_WITH_PERISPOMENI_AND_YPOGEGRAMMENI}, 1);
                }
                else
                {
                    ucsplice(buffer, bufferLen, bufferCapacity, *bufferLen, 0, (UCS2[]){GREEK_SMALL_LETTER_ETA_WITH_PSILI_AND_PERISPOMENI_AND_YPOGEGRAMMENI}, 1);
                }
            }
            else if (vf->mood == OPTATIVE)
            {
                if (!decompose)
                {
                    ucsplice(buffer, bufferLen, bufferCapacity, *bufferLen - 1, 1, (UCS2[]){GREEK_SMALL_LETTER_EPSILON,IOTA_WITH_ACUTE,GREEK_SMALL_LETTER_ETA}, 3);
                }
                else
                {
                    ucsplice(buffer, bufferLen, bufferCapacity, *bufferLen, 0, (UCS2[]){GREEK_SMALL_LETTER_EPSILON,GREEK_SMALL_LETTER_IOTA_WITH_PSILI_AND_OXIA,GREEK_SMALL_LETTER_ETA}, 3);
                }
            }
            else
            {
                return 0;
            }
        }
        else if (vf->tense == IMPERFECT && vf->mood == INDICATIVE)
        {
            if (decompose)
                ucsplice(buffer, bufferLen, bufferCapacity, 0, 0, (UCS2[]){GREEK_SMALL_LETTER_EPSILON}, 1);
            else
                ucsplice(buffer, bufferLen, bufferCapacity, 0, 0, (UCS2[]){GREEK_SMALL_LETTER_EPSILON_WITH_PSILI}, 1);
            
            if (decompose)
            {
                ucsplice(buffer, bufferLen, bufferCapacity, 1, 0, (UCS2[]){SPACE,HYPHEN,SPACE}, 3);
            }
            if (decompose)
            {
                ucsplice(buffer, bufferLen, bufferCapacity, *bufferLen, 0, (UCS2[]){GREEK_SMALL_LETTER_ETA_WITH_PSILI_AND_PERISPOMENI,GREEK_SMALL_LETTER_NU}, 2);
            }
            else
            {
                ucsplice(buffer, bufferLen, bufferCapacity, *bufferLen - 1, 1, (UCS2[]){GREEK_SMALL_LETTER_ETA_WITH_PERISPOMENI,GREEK_SMALL_LETTER_NU,COMMA,SPACE,GREEK_SMALL_LETTER_CHI,GREEK_SMALL_LETTER_RHO,GREEK_SMALL_LETTER_ETA_WITH_PERISPOMENI,GREEK_SMALL_LETTER_NU}, 8);
            }
        }
        else if (vf->tense == FUTURE && vf->mood == INDICATIVE)
        {
            if (decompose)
            {
                ucsplice(buffer, bufferLen, bufferCapacity, *bufferLen, 0, (UCS2[]){GREEK_SMALL_LETTER_EPSILON_WITH_PSILI_AND_OXIA,GREEK_SMALL_LETTER_SIGMA,GREEK_SMALL_LETTER_TAU,GREEK_SMALL_LETTER_ALPHA,GREEK_SMALL_LETTER_IOTA}, 5);
            }
            else
            {
                ucsplice(buffer, bufferLen, bufferCapacity, *bufferLen-1, 1, (UCS2[]){GREEK_SMALL_LETTER_ETA_WITH_PERISPOMENI,GREEK_SMALL_LETTER_SIGMA,GREEK_SMALL_LETTER_TAU,GREEK_SMALL_LETTER_ALPHA,GREEK_SMALL_LETTER_IOTA}, 5);
            }
        }
        else
        {
            //no future optative: H&Q p 565, 566
            return 0;
        }
        return 1;
    }
    else
    {
        return 0;
    }
}


int getOida(VerbFormC *vf, UCS2 *buffer, int *bufferLen, int bufferCapacity, bool decompose)
{
    bool hasPrefix = false;
    if (vf->voice != ACTIVE)
        return 0;
    
    *bufferLen = 0;
    
    if (utf8HasSuffix(vf->verb->present, "σύνοιδα"))
    {
        ucsplice(buffer, bufferLen, bufferCapacity, 0, 0, (UCS2[]){GREEK_SMALL_LETTER_SIGMA,GREEK_SMALL_LETTER_UPSILON,GREEK_SMALL_LETTER_NU}, 3);
        hasPrefix = true;
        
        if (decompose)
        {
            ucsplice(buffer, bufferLen, bufferCapacity, *bufferLen, 0, (UCS2[]){SPACE,HYPHEN,SPACE}, 3);
        }
    }
    
    if (vf->tense == PERFECT)
    {
        if (vf->voice != ACTIVE)
        {
            return 0;
        }
        
        if (vf->mood == INDICATIVE)
        {
            if (vf->number == SINGULAR)
            {
                ucsplice(buffer, bufferLen, bufferCapacity, *bufferLen, 0, (UCS2[]){GREEK_SMALL_LETTER_OMICRON}, 1);
                if (!hasPrefix || decompose)
                    ucsplice(buffer, bufferLen, bufferCapacity, *bufferLen, 0, (UCS2[]){GREEK_SMALL_LETTER_IOTA_WITH_PSILI_AND_PERISPOMENI}, 1);
                else
                    ucsplice(buffer, bufferLen, bufferCapacity, *bufferLen, 0, (UCS2[]){GREEK_SMALL_LETTER_IOTA}, 1);
                if (vf->person == SECOND)
                    ucsplice(buffer, bufferLen, bufferCapacity, *bufferLen, 0, (UCS2[]){GREEK_SMALL_LETTER_SIGMA}, 1);
                else
                    ucsplice(buffer, bufferLen, bufferCapacity, *bufferLen, 0, (UCS2[]){GREEK_SMALL_LETTER_DELTA}, 1);
            }
            else
            {
                if (!hasPrefix || decompose)
                {
                    ucsplice(buffer, bufferLen, bufferCapacity, *bufferLen, 0, (UCS2[]){GREEK_SMALL_LETTER_IOTA_WITH_PSILI}, 1);
                }
                else
                {
                    ucsplice(buffer, bufferLen, bufferCapacity, *bufferLen, 0, (UCS2[]){GREEK_SMALL_LETTER_IOTA}, 1);
                }
                ucsplice(buffer, bufferLen, bufferCapacity, *bufferLen, 0, (UCS2[]){GREEK_SMALL_LETTER_SIGMA}, 1);
            }
            if (decompose)
            {
                ucsplice(buffer, bufferLen, bufferCapacity, *bufferLen, 0, (UCS2[]){SPACE,HYPHEN,SPACE}, 3);
            }
            if (vf->person == FIRST && vf->number == SINGULAR)
            {
                ucsplice(buffer, bufferLen, bufferCapacity, *bufferLen, 0, (UCS2[]){GREEK_SMALL_LETTER_ALPHA}, 1);
            }
            else if (vf->person == SECOND && vf->number == SINGULAR)
            {
                ucsplice(buffer, bufferLen, bufferCapacity, *bufferLen, 0, (UCS2[]){GREEK_SMALL_LETTER_THETA,GREEK_SMALL_LETTER_ALPHA}, 2);
            }
            else if (vf->person == THIRD && vf->number == SINGULAR)
            {
                ucsplice(buffer, bufferLen, bufferCapacity, *bufferLen, 0, (UCS2[]){GREEK_SMALL_LETTER_EPSILON,LEFT_PARENTHESIS,GREEK_SMALL_LETTER_NU,RIGHT_PARENTHESIS}, 4);
            }
            else if (vf->person == FIRST && vf->number == PLURAL)
            {
                ucsplice(buffer, bufferLen, bufferCapacity, *bufferLen, 0, (UCS2[]){GREEK_SMALL_LETTER_MU,GREEK_SMALL_LETTER_EPSILON,GREEK_SMALL_LETTER_NU}, 3);
            }
            else if (vf->person == SECOND && vf->number == PLURAL)
            {
                ucsplice(buffer, bufferLen, bufferCapacity, *bufferLen, 0, (UCS2[]){GREEK_SMALL_LETTER_TAU,GREEK_SMALL_LETTER_EPSILON}, 2);
            }
            else if (vf->person == THIRD && vf->number == PLURAL)
            {
                ucsplice(buffer, bufferLen, bufferCapacity, *bufferLen, 0, (UCS2[]){GREEK_SMALL_LETTER_ALPHA,COMBINING_MACRON,GREEK_SMALL_LETTER_SIGMA,GREEK_SMALL_LETTER_IOTA,LEFT_PARENTHESIS,GREEK_SMALL_LETTER_NU,RIGHT_PARENTHESIS}, 7);
            }
        }
        else if (vf->mood == SUBJUNCTIVE)
        {
            ucsplice(buffer, bufferLen, bufferCapacity, *bufferLen, 0, (UCS2[]){GREEK_SMALL_LETTER_EPSILON}, 1);
            if (hasPrefix && !decompose)
                ucsplice(buffer, bufferLen, bufferCapacity, *bufferLen, 0, (UCS2[]){GREEK_SMALL_LETTER_IOTA}, 1);
            else
                ucsplice(buffer, bufferLen, bufferCapacity, *bufferLen, 0, (UCS2[]){GREEK_SMALL_LETTER_IOTA_WITH_PSILI}, 1);
            ucsplice(buffer, bufferLen, bufferCapacity, *bufferLen, 0, (UCS2[]){GREEK_SMALL_LETTER_DELTA}, 1);
            
            if (decompose)
            {
                ucsplice(buffer, bufferLen, bufferCapacity, *bufferLen, 0, (UCS2[]){GREEK_SMALL_LETTER_EPSILON,SPACE,HYPHEN,SPACE}, 4);
            }
            if (vf->person == FIRST && vf->number == SINGULAR)
            {
                ucsplice(buffer, bufferLen, bufferCapacity, *bufferLen, 0, (UCS2[]){GREEK_SMALL_LETTER_OMEGA_WITH_PERISPOMENI}, 1);
            }
            else if (vf->person == SECOND && vf->number == SINGULAR)
            {
                ucsplice(buffer, bufferLen, bufferCapacity, *bufferLen, 0, (UCS2[]){GREEK_SMALL_LETTER_ETA_WITH_PERISPOMENI_AND_YPOGEGRAMMENI,GREEK_SMALL_LETTER_FINAL_SIGMA}, 2);
            }
            else if (vf->person == THIRD && vf->number == SINGULAR)
            {
                ucsplice(buffer, bufferLen, bufferCapacity, *bufferLen, 0, (UCS2[]){GREEK_SMALL_LETTER_ETA_WITH_PERISPOMENI_AND_YPOGEGRAMMENI}, 1);
            }
            else if (vf->person == FIRST && vf->number == PLURAL)
            {
                ucsplice(buffer, bufferLen, bufferCapacity, *bufferLen, 0, (UCS2[]){GREEK_SMALL_LETTER_OMEGA_WITH_PERISPOMENI,GREEK_SMALL_LETTER_MU,GREEK_SMALL_LETTER_EPSILON,GREEK_SMALL_LETTER_NU}, 4);
            }
            else if (vf->person == SECOND && vf->number == PLURAL)
            {
                ucsplice(buffer, bufferLen, bufferCapacity, *bufferLen, 0, (UCS2[]){GREEK_SMALL_LETTER_ETA_WITH_PERISPOMENI,GREEK_SMALL_LETTER_TAU,GREEK_SMALL_LETTER_EPSILON}, 3);
                
            }
            else if (vf->person == THIRD && vf->number == PLURAL)
            {
                ucsplice(buffer, bufferLen, bufferCapacity, *bufferLen, 0, (UCS2[]){GREEK_SMALL_LETTER_OMEGA_WITH_PERISPOMENI,GREEK_SMALL_LETTER_SIGMA,GREEK_SMALL_LETTER_IOTA,LEFT_PARENTHESIS,GREEK_SMALL_LETTER_NU,RIGHT_PARENTHESIS}, 6);
            }
        }
        else if (vf->mood == OPTATIVE)
        {
            ucsplice(buffer, bufferLen, bufferCapacity, *bufferLen, 0, (UCS2[]){GREEK_SMALL_LETTER_EPSILON}, 1);
            if (hasPrefix && !decompose)
                ucsplice(buffer, bufferLen, bufferCapacity, *bufferLen, 0, (UCS2[]){GREEK_SMALL_LETTER_IOTA}, 1);
            else
                ucsplice(buffer, bufferLen, bufferCapacity, *bufferLen, 0, (UCS2[]){GREEK_SMALL_LETTER_IOTA_WITH_PSILI}, 1);
            ucsplice(buffer, bufferLen, bufferCapacity, *bufferLen, 0, (UCS2[]){GREEK_SMALL_LETTER_DELTA}, 1);
            
            if (decompose)
            {
                ucsplice(buffer, bufferLen, bufferCapacity, *bufferLen, 0, (UCS2[]){SPACE,HYPHEN,SPACE}, 3);
            }
            if (vf->person == FIRST && vf->number == SINGULAR)
            {
                ucsplice(buffer, bufferLen, bufferCapacity, *bufferLen, 0, (UCS2[]){GREEK_SMALL_LETTER_EPSILON,IOTA_WITH_ACUTE,GREEK_SMALL_LETTER_ETA,GREEK_SMALL_LETTER_NU}, 4);
            }
            else if (vf->person == SECOND && vf->number == SINGULAR)
            {
                ucsplice(buffer, bufferLen, bufferCapacity, *bufferLen, 0, (UCS2[]){GREEK_SMALL_LETTER_EPSILON,IOTA_WITH_ACUTE,GREEK_SMALL_LETTER_ETA,GREEK_SMALL_LETTER_FINAL_SIGMA}, 4);
            }
            else if (vf->person == THIRD && vf->number == SINGULAR)
            {
                ucsplice(buffer, bufferLen, bufferCapacity, *bufferLen, 0, (UCS2[]){GREEK_SMALL_LETTER_EPSILON,IOTA_WITH_ACUTE,GREEK_SMALL_LETTER_ETA}, 3);
            }
            else if (vf->person == FIRST && vf->number == PLURAL)
            {
                ucsplice(buffer, bufferLen, bufferCapacity, *bufferLen, 0, (UCS2[]){GREEK_SMALL_LETTER_EPSILON,GREEK_SMALL_LETTER_IOTA_WITH_PERISPOMENI,GREEK_SMALL_LETTER_MU,GREEK_SMALL_LETTER_EPSILON,GREEK_SMALL_LETTER_NU,COMMA,SPACE}, 7);
                if (utf8HasSuffix(vf->verb->present, "σύνοιδα"))
                {
                    ucsplice(buffer, bufferLen, bufferCapacity, *bufferLen, 0, (UCS2[]){GREEK_SMALL_LETTER_SIGMA,GREEK_SMALL_LETTER_UPSILON,GREEK_SMALL_LETTER_NU}, 3);
                    
                    if (decompose)
                    {
                        ucsplice(buffer, bufferLen, bufferCapacity, *bufferLen, 0, (UCS2[]){SPACE,HYPHEN,SPACE}, 3);
                    }
                }
                
                ucsplice(buffer, bufferLen, bufferCapacity, *bufferLen, 0, (UCS2[]){GREEK_SMALL_LETTER_EPSILON}, 1);
                if (hasPrefix && !decompose)
                    ucsplice(buffer, bufferLen, bufferCapacity, *bufferLen, 0, (UCS2[]){GREEK_SMALL_LETTER_IOTA}, 1);
                else
                    ucsplice(buffer, bufferLen, bufferCapacity, *bufferLen, 0, (UCS2[]){GREEK_SMALL_LETTER_IOTA_WITH_PSILI}, 1);
                ucsplice(buffer, bufferLen, bufferCapacity, *bufferLen, 0, (UCS2[]){GREEK_SMALL_LETTER_DELTA}, 1);
                if (decompose)
                {
                    ucsplice(buffer, bufferLen, bufferCapacity, *bufferLen, 0, (UCS2[]){SPACE,HYPHEN,SPACE}, 3);
                }
                
                ucsplice(buffer, bufferLen, bufferCapacity, *bufferLen, 0, (UCS2[]){GREEK_SMALL_LETTER_EPSILON,IOTA_WITH_ACUTE,GREEK_SMALL_LETTER_ETA,GREEK_SMALL_LETTER_MU,GREEK_SMALL_LETTER_EPSILON,GREEK_SMALL_LETTER_NU}, 6);
            }
            else if (vf->person == SECOND && vf->number == PLURAL)
            {
                ucsplice(buffer, bufferLen, bufferCapacity, *bufferLen, 0, (UCS2[]){GREEK_SMALL_LETTER_EPSILON,GREEK_SMALL_LETTER_IOTA_WITH_PERISPOMENI,GREEK_SMALL_LETTER_TAU,GREEK_SMALL_LETTER_EPSILON,COMMA,SPACE}, 6);
                if (utf8HasSuffix(vf->verb->present, "σύνοιδα"))
                {
                    ucsplice(buffer, bufferLen, bufferCapacity, *bufferLen, 0, (UCS2[]){GREEK_SMALL_LETTER_SIGMA,GREEK_SMALL_LETTER_UPSILON,GREEK_SMALL_LETTER_NU}, 3);
                    
                    if (decompose)
                    {
                        ucsplice(buffer, bufferLen, bufferCapacity, *bufferLen, 0, (UCS2[]){SPACE,HYPHEN,SPACE}, 3);
                    }
                }
                
                ucsplice(buffer, bufferLen, bufferCapacity, *bufferLen, 0, (UCS2[]){GREEK_SMALL_LETTER_EPSILON}, 1);
                if (hasPrefix && !decompose)
                    ucsplice(buffer, bufferLen, bufferCapacity, *bufferLen, 0, (UCS2[]){GREEK_SMALL_LETTER_IOTA}, 1);
                else
                    ucsplice(buffer, bufferLen, bufferCapacity, *bufferLen, 0, (UCS2[]){GREEK_SMALL_LETTER_IOTA_WITH_PSILI}, 1);
                ucsplice(buffer, bufferLen, bufferCapacity, *bufferLen, 0, (UCS2[]){GREEK_SMALL_LETTER_DELTA}, 1);
                if (decompose)
                {
                    ucsplice(buffer, bufferLen, bufferCapacity, *bufferLen, 0, (UCS2[]){SPACE,HYPHEN,SPACE}, 3);
                }
                
                ucsplice(buffer, bufferLen, bufferCapacity, *bufferLen, 0, (UCS2[]){GREEK_SMALL_LETTER_EPSILON,IOTA_WITH_ACUTE,GREEK_SMALL_LETTER_ETA,GREEK_SMALL_LETTER_TAU,GREEK_SMALL_LETTER_EPSILON}, 5);
            }
            else if (vf->person == THIRD && vf->number == PLURAL)
            {
                ucsplice(buffer, bufferLen, bufferCapacity, *bufferLen, 0, (UCS2[]){GREEK_SMALL_LETTER_EPSILON,GREEK_SMALL_LETTER_IOTA_WITH_PERISPOMENI,GREEK_SMALL_LETTER_EPSILON,GREEK_SMALL_LETTER_NU,COMMA,SPACE}, 6);
                if (utf8HasSuffix(vf->verb->present, "σύνοιδα"))
                {
                    ucsplice(buffer, bufferLen, bufferCapacity, *bufferLen, 0, (UCS2[]){GREEK_SMALL_LETTER_SIGMA,GREEK_SMALL_LETTER_UPSILON,GREEK_SMALL_LETTER_NU}, 3);
                    
                    if (decompose)
                    {
                        ucsplice(buffer, bufferLen, bufferCapacity, *bufferLen, 0, (UCS2[]){SPACE,HYPHEN,SPACE}, 3);
                    }
                }
                
                ucsplice(buffer, bufferLen, bufferCapacity, *bufferLen, 0, (UCS2[]){GREEK_SMALL_LETTER_EPSILON}, 1);
                if (hasPrefix && !decompose)
                    ucsplice(buffer, bufferLen, bufferCapacity, *bufferLen, 0, (UCS2[]){GREEK_SMALL_LETTER_IOTA}, 1);
                else
                    ucsplice(buffer, bufferLen, bufferCapacity, *bufferLen, 0, (UCS2[]){GREEK_SMALL_LETTER_IOTA_WITH_PSILI}, 1);
                ucsplice(buffer, bufferLen, bufferCapacity, *bufferLen, 0, (UCS2[]){GREEK_SMALL_LETTER_DELTA}, 1);
                if (decompose)
                {
                    ucsplice(buffer, bufferLen, bufferCapacity, *bufferLen, 0, (UCS2[]){SPACE,HYPHEN,SPACE}, 3);
                }
                
                ucsplice(buffer, bufferLen, bufferCapacity, *bufferLen, 0, (UCS2[]){GREEK_SMALL_LETTER_EPSILON,IOTA_WITH_ACUTE,GREEK_SMALL_LETTER_ETA,GREEK_SMALL_LETTER_SIGMA,GREEK_SMALL_LETTER_ALPHA,GREEK_SMALL_LETTER_NU}, 6);
            }
        }
        else if (vf->mood == IMPERATIVE)
        {
            if (!hasPrefix || decompose)
                ucsplice(buffer, bufferLen, bufferCapacity, *bufferLen, 0, (UCS2[]){GREEK_SMALL_LETTER_IOTA_WITH_PSILI}, 1);
            else
                ucsplice(buffer, bufferLen, bufferCapacity, *bufferLen, 0, (UCS2[]){GREEK_SMALL_LETTER_IOTA}, 1);
            
            ucsplice(buffer, bufferLen, bufferCapacity, *bufferLen, 0, (UCS2[]){GREEK_SMALL_LETTER_SIGMA}, 1);
            if (decompose)
            {
                ucsplice(buffer, bufferLen, bufferCapacity, *bufferLen, 0, (UCS2[]){SPACE,HYPHEN,SPACE}, 3);
                
            }
            if (vf->person == FIRST && vf->number == SINGULAR)
            {
                return 0;
            }
            else if (vf->person == SECOND && vf->number == SINGULAR)
            {
                ucsplice(buffer, bufferLen, bufferCapacity, *bufferLen, 0, (UCS2[]){GREEK_SMALL_LETTER_THETA,GREEK_SMALL_LETTER_IOTA}, 2);
            }
            else if (vf->person == THIRD && vf->number == SINGULAR)
            {
                ucsplice(buffer, bufferLen, bufferCapacity, *bufferLen, 0, (UCS2[]){GREEK_SMALL_LETTER_TAU,GREEK_SMALL_LETTER_OMEGA}, 2);
            }
            else if (vf->person == FIRST && vf->number == PLURAL)
            {
                return 0;
            }
            else if (vf->person == SECOND && vf->number == PLURAL)
            {
                ucsplice(buffer, bufferLen, bufferCapacity, *bufferLen, 0, (UCS2[]){GREEK_SMALL_LETTER_TAU,GREEK_SMALL_LETTER_EPSILON}, 2);
            }
            else if (vf->person == THIRD && vf->number == PLURAL)
            {
                ucsplice(buffer, bufferLen, bufferCapacity, *bufferLen, 0, (UCS2[]){GREEK_SMALL_LETTER_TAU,GREEK_SMALL_LETTER_OMEGA,GREEK_SMALL_LETTER_NU}, 3);
            }
        }
    }
    else if (vf->tense == PLUPERFECT)
    {
        if (vf->mood != INDICATIVE)
        {
            return 0;
        }
        if (vf->voice != ACTIVE)
        {
            return 0;
        }
        
        if (!decompose)
        {
            if (!hasPrefix && vf->number == SINGULAR)
                ucsplice(buffer, bufferLen, bufferCapacity, *bufferLen, 0, (UCS2[]){GREEK_SMALL_LETTER_ETA_WITH_PSILI_AND_OXIA_AND_YPOGEGRAMMENI}, 1);
            else if ( vf->number == SINGULAR )
                ucsplice(buffer, bufferLen, bufferCapacity, *bufferLen, 0, (UCS2[]){GREEK_SMALL_LETTER_ETA_WITH_OXIA_AND_YPOGEGRAMMENI}, 1);
            else if (!hasPrefix && vf->number == PLURAL)
                ucsplice(buffer, bufferLen, bufferCapacity, *bufferLen, 0, (UCS2[]){GREEK_SMALL_LETTER_ETA_WITH_PSILI_AND_PERISPOMENI_AND_YPOGEGRAMMENI}, 1);
            else if ( vf->number == PLURAL)
                ucsplice(buffer, bufferLen, bufferCapacity, *bufferLen, 0, (UCS2[]){GREEK_SMALL_LETTER_ETA_WITH_PERISPOMENI_AND_YPOGEGRAMMENI}, 1);
            
            if (vf->number == SINGULAR)
                ucsplice(buffer, bufferLen, bufferCapacity, *bufferLen, 0, (UCS2[]){GREEK_SMALL_LETTER_DELTA}, 1);
            else
                ucsplice(buffer, bufferLen, bufferCapacity, *bufferLen, 0, (UCS2[]){GREEK_SMALL_LETTER_SIGMA}, 1);
        }
        else
        {
            ucsplice(buffer, bufferLen, bufferCapacity, *bufferLen, 0, (UCS2[]){DECOMPOSED_AUGMENT_CHAR,SPACE,HYPHEN,SPACE,GREEK_SMALL_LETTER_EPSILON,GREEK_SMALL_LETTER_IOTA_WITH_PSILI}, 6);
            
            if (vf->number == SINGULAR)
                ucsplice(buffer, bufferLen, bufferCapacity, *bufferLen, 0, (UCS2[]){GREEK_SMALL_LETTER_DELTA}, 1);
            else
                ucsplice(buffer, bufferLen, bufferCapacity, *bufferLen, 0, (UCS2[]){GREEK_SMALL_LETTER_SIGMA}, 1);
        }
        
        if (decompose)
        {
            ucsplice(buffer, bufferLen, bufferCapacity, *bufferLen, 0, (UCS2[]){SPACE,HYPHEN,SPACE}, 3);
        }
        if (vf->person == FIRST && vf->number == SINGULAR)
        {
            ucsplice(buffer, bufferLen, bufferCapacity, *bufferLen, 0, (UCS2[]){GREEK_SMALL_LETTER_ETA,COMMA,SPACE}, 3);
            
            if (utf8HasSuffix(vf->verb->present, "σύνοιδα"))
            {
                ucsplice(buffer, bufferLen, bufferCapacity, *bufferLen, 0, (UCS2[]){GREEK_SMALL_LETTER_SIGMA,GREEK_SMALL_LETTER_UPSILON,GREEK_SMALL_LETTER_NU}, 3);
                
                if (decompose)
                {
                    ucsplice(buffer, bufferLen, bufferCapacity, *bufferLen, 0, (UCS2[]){SPACE,HYPHEN,SPACE}, 3);
                }
            }
            
            if (hasPrefix && !decompose)
            {
                ucsplice(buffer, bufferLen, bufferCapacity, *bufferLen, 0, (UCS2[]){GREEK_SMALL_LETTER_ETA_WITH_OXIA_AND_YPOGEGRAMMENI}, 1);
            }
            else if (decompose)
            {
                ucsplice(buffer, bufferLen, bufferCapacity, *bufferLen, 0, (UCS2[]){DECOMPOSED_AUGMENT_CHAR,SPACE,HYPHEN,SPACE,GREEK_SMALL_LETTER_EPSILON,GREEK_SMALL_LETTER_IOTA_WITH_PSILI}, 6);
            }
            else
            {
                ucsplice(buffer, bufferLen, bufferCapacity, *bufferLen, 0, (UCS2[]){GREEK_SMALL_LETTER_ETA_WITH_PSILI_AND_OXIA_AND_YPOGEGRAMMENI}, 1);
            }
            ucsplice(buffer, bufferLen, bufferCapacity, *bufferLen, 0, (UCS2[]){GREEK_SMALL_LETTER_DELTA}, 1);
            
            if (decompose)
            {
                ucsplice(buffer, bufferLen, bufferCapacity, *bufferLen, 0, (UCS2[]){SPACE,HYPHEN,SPACE}, 3);
            }
            
            ucsplice(buffer, bufferLen, bufferCapacity, *bufferLen, 0, (UCS2[]){GREEK_SMALL_LETTER_EPSILON,GREEK_SMALL_LETTER_IOTA,GREEK_SMALL_LETTER_NU}, 3);
        }
        else if (vf->person == SECOND && vf->number == SINGULAR)
        {
            ucsplice(buffer, bufferLen, bufferCapacity, *bufferLen, 0, (UCS2[]){GREEK_SMALL_LETTER_ETA,GREEK_SMALL_LETTER_SIGMA,GREEK_SMALL_LETTER_THETA,GREEK_SMALL_LETTER_ALPHA,COMMA,SPACE}, 6);
            
            if (utf8HasSuffix(vf->verb->present, "σύνοιδα"))
            {
                ucsplice(buffer, bufferLen, bufferCapacity, *bufferLen, 0, (UCS2[]){GREEK_SMALL_LETTER_SIGMA,GREEK_SMALL_LETTER_UPSILON,GREEK_SMALL_LETTER_NU}, 3);
                
                if (decompose)
                {
                    ucsplice(buffer, bufferLen, bufferCapacity, *bufferLen, 0, (UCS2[]){SPACE,HYPHEN,SPACE}, 3);
                }
            }
            
            if (hasPrefix && !decompose)
            {
                ucsplice(buffer, bufferLen, bufferCapacity, *bufferLen, 0, (UCS2[]){GREEK_SMALL_LETTER_ETA_WITH_OXIA_AND_YPOGEGRAMMENI}, 1);
            }
            else if (decompose)
            {
                ucsplice(buffer, bufferLen, bufferCapacity, *bufferLen, 0, (UCS2[]){DECOMPOSED_AUGMENT_CHAR,SPACE,HYPHEN,SPACE,GREEK_SMALL_LETTER_EPSILON,GREEK_SMALL_LETTER_IOTA_WITH_PSILI}, 6);
            }
            else
            {
                ucsplice(buffer, bufferLen, bufferCapacity, *bufferLen, 0, (UCS2[]){GREEK_SMALL_LETTER_ETA_WITH_PSILI_AND_OXIA_AND_YPOGEGRAMMENI}, 1);
            }
            ucsplice(buffer, bufferLen, bufferCapacity, *bufferLen, 0, (UCS2[]){GREEK_SMALL_LETTER_DELTA}, 1);
            
            if (decompose)
            {
                ucsplice(buffer, bufferLen, bufferCapacity, *bufferLen, 0, (UCS2[]){SPACE,HYPHEN,SPACE}, 3);
            }
            
            ucsplice(buffer, bufferLen, bufferCapacity, *bufferLen, 0, (UCS2[]){GREEK_SMALL_LETTER_EPSILON,GREEK_SMALL_LETTER_IOTA,GREEK_SMALL_LETTER_FINAL_SIGMA}, 3);
        }
        else if (vf->person == THIRD && vf->number == SINGULAR)
        {
            ucsplice(buffer, bufferLen, bufferCapacity, *bufferLen, 0, (UCS2[]){GREEK_SMALL_LETTER_EPSILON,GREEK_SMALL_LETTER_IOTA,LEFT_PARENTHESIS,GREEK_SMALL_LETTER_NU,RIGHT_PARENTHESIS}, 5);
        }
        else if (vf->person == FIRST && vf->number == PLURAL)
        {
            ucsplice(buffer, bufferLen, bufferCapacity, *bufferLen, 0, (UCS2[]){GREEK_SMALL_LETTER_MU,GREEK_SMALL_LETTER_EPSILON,GREEK_SMALL_LETTER_NU,COMMA,SPACE}, 5);
            
            if (utf8HasSuffix(vf->verb->present, "σύνοιδα"))
            {
                ucsplice(buffer, bufferLen, bufferCapacity, *bufferLen, 0, (UCS2[]){GREEK_SMALL_LETTER_SIGMA,GREEK_SMALL_LETTER_UPSILON,GREEK_SMALL_LETTER_NU}, 3);
                
                if (decompose)
                {
                    ucsplice(buffer, bufferLen, bufferCapacity, *bufferLen, 0, (UCS2[]){SPACE,HYPHEN,SPACE}, 3);
                }
            }
            
            if (hasPrefix && !decompose)
            {
                ucsplice(buffer, bufferLen, bufferCapacity, *bufferLen, 0, (UCS2[]){GREEK_SMALL_LETTER_ETA_WITH_OXIA_AND_YPOGEGRAMMENI}, 1);
            }
            else if (decompose)
            {
                ucsplice(buffer, bufferLen, bufferCapacity, *bufferLen, 0, (UCS2[]){DECOMPOSED_AUGMENT_CHAR,SPACE,HYPHEN,SPACE,GREEK_SMALL_LETTER_EPSILON,GREEK_SMALL_LETTER_IOTA_WITH_PSILI}, 6);
            }
            else
            {
                ucsplice(buffer, bufferLen, bufferCapacity, *bufferLen, 0, (UCS2[]){GREEK_SMALL_LETTER_ETA_WITH_PSILI_AND_OXIA_AND_YPOGEGRAMMENI}, 1);
            }
            
            ucsplice(buffer, bufferLen, bufferCapacity, *bufferLen, 0, (UCS2[]){GREEK_SMALL_LETTER_DELTA}, 1);
            
            if (decompose)
            {
                ucsplice(buffer, bufferLen, bufferCapacity, *bufferLen, 0, (UCS2[]){SPACE,HYPHEN,SPACE}, 3);
            }
            
            ucsplice(buffer, bufferLen, bufferCapacity, *bufferLen, 0, (UCS2[]){GREEK_SMALL_LETTER_EPSILON,GREEK_SMALL_LETTER_MU,GREEK_SMALL_LETTER_EPSILON,GREEK_SMALL_LETTER_NU}, 4);
        }
        else if (vf->person == SECOND && vf->number == PLURAL)
        {
            ucsplice(buffer, bufferLen, bufferCapacity, *bufferLen, 0, (UCS2[]){GREEK_SMALL_LETTER_TAU,GREEK_SMALL_LETTER_EPSILON,COMMA,SPACE}, 4);
            
            if (utf8HasSuffix(vf->verb->present, "σύνοιδα"))
            {
                ucsplice(buffer, bufferLen, bufferCapacity, *bufferLen, 0, (UCS2[]){GREEK_SMALL_LETTER_SIGMA,GREEK_SMALL_LETTER_UPSILON,GREEK_SMALL_LETTER_NU}, 3);
                
                if (decompose)
                {
                    ucsplice(buffer, bufferLen, bufferCapacity, *bufferLen, 0, (UCS2[]){SPACE,HYPHEN,SPACE}, 3);
                }
            }
            
            if (hasPrefix && !decompose)
            {
                ucsplice(buffer, bufferLen, bufferCapacity, *bufferLen, 0, (UCS2[]){GREEK_SMALL_LETTER_ETA_WITH_OXIA_AND_YPOGEGRAMMENI}, 1);
            }
            else if (decompose)
            {
                ucsplice(buffer, bufferLen, bufferCapacity, *bufferLen, 0, (UCS2[]){DECOMPOSED_AUGMENT_CHAR,SPACE,HYPHEN,SPACE,GREEK_SMALL_LETTER_EPSILON,GREEK_SMALL_LETTER_IOTA_WITH_PSILI}, 6);
            }
            else
            {
                ucsplice(buffer, bufferLen, bufferCapacity, *bufferLen, 0, (UCS2[]){GREEK_SMALL_LETTER_ETA_WITH_PSILI_AND_OXIA_AND_YPOGEGRAMMENI}, 1);
            }
            
            ucsplice(buffer, bufferLen, bufferCapacity, *bufferLen, 0, (UCS2[]){GREEK_SMALL_LETTER_DELTA}, 1);
            
            if (decompose)
            {
                ucsplice(buffer, bufferLen, bufferCapacity, *bufferLen, 0, (UCS2[]){SPACE,HYPHEN,SPACE}, 3);
            }
            
            ucsplice(buffer, bufferLen, bufferCapacity, *bufferLen, 0, (UCS2[]){GREEK_SMALL_LETTER_EPSILON,GREEK_SMALL_LETTER_TAU,GREEK_SMALL_LETTER_EPSILON}, 3);
        }
        else if (vf->person == THIRD && vf->number == PLURAL)
        {
            ucsplice(buffer, bufferLen, bufferCapacity, *bufferLen, 0, (UCS2[]){GREEK_SMALL_LETTER_ALPHA,GREEK_SMALL_LETTER_NU,COMMA,SPACE}, 4);
            
            if (utf8HasSuffix(vf->verb->present, "σύνοιδα"))
            {
                ucsplice(buffer, bufferLen, bufferCapacity, *bufferLen, 0, (UCS2[]){GREEK_SMALL_LETTER_SIGMA,GREEK_SMALL_LETTER_UPSILON,GREEK_SMALL_LETTER_NU}, 3);
                
                if (decompose)
                {
                    ucsplice(buffer, bufferLen, bufferCapacity, *bufferLen, 0, (UCS2[]){SPACE,HYPHEN,SPACE}, 3);
                }
            }
            
            if (hasPrefix && !decompose)
            {
                ucsplice(buffer, bufferLen, bufferCapacity, *bufferLen, 0, (UCS2[]){GREEK_SMALL_LETTER_ETA_WITH_OXIA_AND_YPOGEGRAMMENI}, 1);
            }
            else if (decompose)
            {
                ucsplice(buffer, bufferLen, bufferCapacity, *bufferLen, 0, (UCS2[]){DECOMPOSED_AUGMENT_CHAR,SPACE,HYPHEN,SPACE,GREEK_SMALL_LETTER_EPSILON,GREEK_SMALL_LETTER_IOTA_WITH_PSILI}, 6);
            }
            else
            {
                ucsplice(buffer, bufferLen, bufferCapacity, *bufferLen, 0, (UCS2[]){GREEK_SMALL_LETTER_ETA_WITH_PSILI_AND_OXIA_AND_YPOGEGRAMMENI}, 1);
            }
            
            ucsplice(buffer, bufferLen, bufferCapacity, *bufferLen, 0, (UCS2[]){GREEK_SMALL_LETTER_DELTA}, 1);
            
            if (decompose)
            {
                ucsplice(buffer, bufferLen, bufferCapacity, *bufferLen, 0, (UCS2[]){SPACE,HYPHEN,SPACE}, 3);
            }
            
            ucsplice(buffer, bufferLen, bufferCapacity, *bufferLen, 0, (UCS2[]){GREEK_SMALL_LETTER_EPSILON,GREEK_SMALL_LETTER_SIGMA,GREEK_SMALL_LETTER_ALPHA,GREEK_SMALL_LETTER_NU}, 4);
        }
    }
    else
    {
        return 0;
    }
    
    return 1;
}
