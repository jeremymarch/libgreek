/*
Use:
gcc -std=c99 checkVerbForms2.c ../libmorph.c ../GreekForms.c ../accent.c ../utilities.c ../augment.c ../ending.c -I.. -o checkVerbForms2
./checkVerbForms2
diff -u 2017-03-23_19-23-18.txt 2017-03-23_19-25-58.txt
*/

#include <time.h>
#include <stdlib.h> // For random(), RAND_MAX
#include <string.h>  //for strlen
#include <stdbool.h> //for bool type
#include "libmorph.h"

extern Verb verbs[];
extern char *tenses[];
extern char *moods[];
extern char *voices[];

int numVerbs = 127;

void getCurrentTime(char *buffer, int bufferLen)
{
    time_t now = time(NULL);
    strftime(buffer, bufferLen, "%Y-%m-%d_%H-%M-%S.txt", localtime(&now));
}

int main(int argc, char **argv)
{
    int fileBufferLen = 100;
    char fileBuffer[fileBufferLen];

    getCurrentTime(fileBuffer, fileBufferLen);
    FILE *fp = fopen("new.txt"/*fileBuffer*/, "wb");

    VerbFormC vf;
    VerbFormC longestVF;
    VerbFormC longestVFDecomposed;
    vf.mood = INDICATIVE;
    int rowCount = 0;
    int totalNumForms = 0;
    int bufferLen = 50;
    char buffer[bufferLen];
    int bufferLen2 = 137;
    char buffer2[bufferLen2];

    int MFZero = 0;
    int MFOne = 0;
    int MFTwo = 0;
    int MFThree = 0;
    int MFFour = 0;
    int MFFive = 0;
    int MFMore = 0;
    int longestForm = 0;
    int longestFormDecomposed = 0;
    char *noFormLabel = "NF";
    char *noDCFormLabel = "NDF";

//numVerbs = 1;
    for (int verbi = 0; verbi < numVerbs; verbi++)
    {
        vf.verb = &verbs[verbi];
        char *voiceO;
        char *voiceMiddlePassive = " (Middle/Passive)";
        char *voiceNotMiddlePassive = "";
        
        char *depo;
        char *depMid = " (Middle Deponent)";
        char *depPass = " (Passive Deponent)";
        char *depPart = " (Partial Deponent)";
        char *depGig = " (Deponent gignomai)";
        if (deponentType(vf.verb) == MIDDLE_DEPONENT)
            depo = depMid;
        else if (deponentType(vf.verb) == PASSIVE_DEPONENT)
            depo = depMid;
        else if (deponentType(vf.verb) == PARTIAL_DEPONENT)
            depo = depPart;
        else if (deponentType(vf.verb) == DEPONENT_GIGNOMAI)
            depo = depGig;
        else
            depo = NULL;

        fprintf(fp, "\nVerb %d. %s%s\n", verbi, (strlen(verbs[verbi].present) > 0) ? verbs[verbi].present : verbs[verbi].future, (depo) ? depo : "");
        for (int g1 = 0; g1 < NUM_TENSES; g1++)
        {
            vf.tense = g1;
            for (int v = 0; v < NUM_VOICES; v++)
            {
                for (int m = 0; m < NUM_MOODS; m++)
                {
                    //add exception for oida here
                    if (m != INDICATIVE && (g1 == PERFECT || g1 == PLUPERFECT || g1 == IMPERFECT || (g1 == FUTURE && m != OPTATIVE)))
                        continue;

                    vf.voice = v;
                    int countPerSection = 0;
                    for (int h = 0; h < NUM_NUMBERS; h++)
                    {
                        for (int i = 0; i < NUM_PERSONS; i++)
                        {
                            vf.number = h;
                            vf.person = i;
                            vf.mood = m;
                            bool hasComposed = getForm(&vf, buffer, bufferLen, true, false);
                            bool hasDecomposed = getForm(&vf, buffer2, bufferLen2, true, true);

                                if (countPerSection == 0 && vf.person == FIRST && vf.number == SINGULAR) //== first item, so add label first
                                {
                                    int res = getVoiceDescription1(&vf);
                                    if (res == MIDDLEPASSIVE)
                                    {
                                        voiceO = voiceMiddlePassive;
                                    }
                                    else
                                    {
                                        voiceO = voiceNotMiddlePassive;
                                    }
                                    if (v == ACTIVE || g1 == AORIST || g1 == FUTURE)
                                    {
                                        fprintf(fp, "\n%s %s%s %s\n", tenses[g1], voices[v], voiceO, moods[m]);
                                    }
                                    else if (v == MIDDLE)
                                    {
                                        //FIX ME, is this right?? how do we label these?
                                        //if ( deponentType(vf.verb) == MIDDLE_DEPONENT || deponentType(vf.verb) == PASSIVE_DEPONENT)
                                        //{
                                            fprintf(fp, "\n%s %s%s %s\n", tenses[g1], "Middle", voiceO, moods[m]);
                                        //}
                                        //else
                                        //{
                                        //    fprintf(fp, "\n%s %s %s\n", tenses[g1], "Middle/Passive", moods[m]);
                                        //}
                                    }
                                    else
                                    {
                                        fprintf(fp, "\n%s %s%s %s\n", tenses[g1], "Passive", voiceO, moods[m]);
                                        //yes we want to show them! //continue; //skip passive if middle+passive are the same
                                    }
                                } //end label conditional

                            if (!hasComposed)
                            {
                                strncpy(buffer, noFormLabel, strlen(noFormLabel) * sizeof(char));
                                buffer[strlen(noFormLabel)] = '\0';
                            }
                            if (!hasDecomposed)
                            {
                                strncpy(buffer2, noDCFormLabel, strlen(noDCFormLabel) * sizeof(char));
                                buffer2[strlen(noDCFormLabel)] = '\0';
                            }
                            fprintf(fp, "%d%c: %s ; %s\n", vf.person + 1, (vf.number == 0) ? 's' : 'p', buffer, buffer2);

                            if (hasComposed && hasDecomposed)
                            {
                                int thisNumForms = 0;
                                if (strncmp(buffer, "—", 2))
                                {
                                    thisNumForms++;
                                    totalNumForms++;
                                }

                                int utf8BufferLen = strlen(buffer);
                                //find the longest forms
                                if (longestForm < utf8BufferLen)
                                {
                                    longestForm = utf8BufferLen;
                                    longestVF.verb = vf.verb;
                                    longestVF.person = vf.person;
                                    longestVF.number = vf.number;
                                    longestVF.tense = vf.tense;
                                    longestVF.voice = vf.voice;
                                    longestVF.mood = vf.mood;
                                }

                                int utf8BufferLenDecomposed = strlen(buffer2);
                                //find the longest forms
                                if (longestFormDecomposed < utf8BufferLenDecomposed)
                                {
                                    longestFormDecomposed = utf8BufferLenDecomposed;
                                    longestVFDecomposed.verb = vf.verb;
                                    longestVFDecomposed.person = vf.person;
                                    longestVFDecomposed.number = vf.number;
                                    longestVFDecomposed.tense = vf.tense;
                                    longestVFDecomposed.voice = vf.voice;
                                    longestVFDecomposed.mood = vf.mood;
                                }

                                for (int z = 0; z < utf8BufferLen; z++)
                                {
                                    if (buffer[z] == ',')
                                    {
                                        thisNumForms++;
                                        totalNumForms++;
                                    }
                                }
                                switch(thisNumForms)
                                {
                                    case 0:
                                        MFZero++;
                                        break;
                                    case 1:
                                        MFOne++;
                                        break;
                                    case 2:
                                        MFTwo++;
                                        break;
                                    case 3:
                                        MFThree++;
                                        break;
                                    case 4:
                                        MFFour++;
                                        break;
                                    case 5:
                                        MFFive++;
                                        break;
                                    default:
                                        MFMore++;
                                        break;
                                }

                                countPerSection++;
                                rowCount++;
                            }
                        }
                    }
                }
            }
        }
    }

    fprintf(fp, "\nTotal rows including -: %d\n", rowCount);
    fprintf(fp, "Total forms including alternates, minus -: %d\n\n", totalNumForms);
    fprintf(fp, "Zero Forms: %d\n", MFZero);
    fprintf(fp, "One Form: %d\n", MFOne);
    fprintf(fp, "Two Forms: %d\n", MFTwo);
    fprintf(fp, "Three Forms: %d\n", MFThree);
    fprintf(fp, "Four Forms: %d\n", MFFour);
    fprintf(fp, "Five Forms: %d\n", MFFive);
    fprintf(fp, "More Forms: %d\n", MFMore);
    fprintf(fp, "Total Forms: %d = %d\n", (MFOne + (MFTwo*2) + (MFThree*3) + (MFFour*4) + (MFFive*5) + MFMore), totalNumForms);

    if (getForm(&longestVF, buffer, bufferLen, true, false))
    {
        fprintf(fp, "\nLongest Form: %d,%d,%d,%d,%d, v: %s, l: %lu\n", longestVF.person, longestVF.number, longestVF.tense, longestVF.voice, longestVF.mood, buffer, strlen(buffer));
    }
    if (getForm(&longestVFDecomposed, buffer2, bufferLen, true, true))
    {
        fprintf(fp, "\nLongest Decomposed Form: %d,%d,%d,%d,%d, v: %s, l: %lu\n", longestVFDecomposed.person, longestVFDecomposed.number, longestVFDecomposed.tense, longestVFDecomposed.voice, longestVFDecomposed.mood, buffer2, strlen(buffer2));
    }
    return 0;
}
