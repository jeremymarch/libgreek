//
//  GreekForms.c
//  morph
//
//  Created by Jeremy on 4/28/15.
//  Copyright (c) 2015 Jeremy March. All rights reserved.
//

#include "GreekForms.h"

const Verb verbs[NUM_VERBS] = {
    { 0, 43, 0, 1, "παιδεύω", "παιδεύσω", "ἐπαίδευσα", "πεπαίδευκα", "πεπαίδευμαι", "ἐπαιδεύθην" },
    { 1, 45, CONSONANT_STEM_PERFECT_MU_PI, 1, "πέμπω", "πέμψω", "ἔπεμψα", "πέπομφα", "πέπεμμαι", "ἐπέμφθην" },
    
    { 2, 36, CONSONANT_STEM_PERFECT_SIGMA, 2, "κελεύω", "κελεύσω", "ἐκέλευσα", "κεκέλευκα", "κεκέλευσμαι", "ἐκελεύσθην" },
    { 3, 37, 0, 2, "λῡ́ω", "λῡ́σω", "ἔλῡσα", "λέλυκα", "λέλυμαι", "ἐλύθην" },

    { 4, 58, CONSONANT_STEM_PERFECT_PHI, 3, "γράφω", "γράψω", "ἔγραψα", "γέγραφα", "γέγραμμαι", "ἐγράφην" },
    { 5, 66, 0, 3, "θῡ́ω", "θῡ́σω", "ἔθῡσα", "τέθυκα", "τέθυμαι", "ἐτύθην" },
    { 6, 73, 0, 3, "παύω", "παύσω", "ἔπαυσα", "πέπαυκα", "πέπαυμαι", "ἐπαύθην" },
    { 7, 75, CONSONANT_STEM_PERFECT_KAPPA, 3, "φυλάττω", "φυλάξω", "ἐφύλαξα", "πεφύλαχα", "πεφύλαγμαι", "ἐφυλάχθην" },
    
    { 8, 83, CONSONANT_STEM_PERFECT_KAPPA, 4, "διδάσκω", "διδάξω", "ἐδίδαξα", "δεδίδαχα", "δεδίδαγμαι", "ἐδιδάχθην" },
    { 9, 87, 0, 4, "ἐθέλω", "ἐθελήσω", "ἠθέλησα", "ἠθέληκα", "", "" },
    { 10, 92, CONSONANT_STEM_PERFECT_PI, 4, "θάπτω", "θάψω", "ἔθαψα", "", "τέθαμμαι", "ἐτάφην" },
    { 11, 107, CONSONANT_STEM_PERFECT_GAMMA, 4, "τάττω", "τάξω", "ἔταξα", "τέταχα", "τέταγμαι", "ἐτάχθην" },
    
    { 12, 111, CONSONANT_STEM_PERFECT_CHI, 5, "ἄρχω", "ἄρξω", "ἦρξα", "ἦρχα", "ἦργμαι", "ἤρχθην" },
    { 13, 112, CONSONANT_STEM_PERFECT_BETA, 5, "βλάπτω", "βλάψω", "ἔβλαψα", "βέβλαφα", "βέβλαμμαι", "ἐβλάβην, ἐβλάφθην" },
    { 14, 127, CONSONANT_STEM_PERFECT_SIGMA, 5, "πείθω", "πείσω", "ἔπεισα", "πέπεικα", "πέπεισμαι", "ἐπείσθην" }, //keep πέποιθα?
    { 15, 129, CONSONANT_STEM_PERFECT_GAMMA, 5, "πρᾱ́ττω", "πρᾱ́ξω", "ἔπρᾱξα", "πέπρᾱχα, πέπρᾱγα", "πέπρᾱγμαι", "ἐπρᾱ́χθην" },
    
    { 16, 141, 0, 6, "δουλεύω", "δουλεύσω", "ἐδούλευσα", "δεδούλευκα", "", "" },
    { 17, 147, 0, 6, "κωλῡ́ω", "κωλῡ́σω", "ἐκώλῡσα", "κεκώλῡκα", "κεκώλῡμαι", "ἐκωλῡ́θην" },

    { 18, 151, 0, 6, "πολῑτεύω", "πολῑτεύσω", "ἐπολῑ́τευσα", "πεπολῑ́τευκα", "πεπολῑ́τευμαι", "ἐπολῑτεύθην" },
    { 19, 164, 0, 6, "χορεύω", "χορεύσω", "ἐχόρευσα", "κεχόρευκα", "κεχόρευμαι", "ἐχορεύθην" },
   
    { 20, 178, CONSONANT_STEM_PERFECT_PI, 7, "κλέπτω", "κλέψω", "ἔκλεψα", "κέκλοφα", "κέκλεμμαι", "ἐκλάπην" },
    { 21, 181, CONSONANT_STEM_PERFECT_PI, 7, "λείπω", "λείψω", "ἔλιπον", "λέλοιπα", "λέλειμμαι", "ἐλείφθην" },
    { 22, 186, CONSONANT_STEM_PERFECT_SIGMA_2, 7, "σῴζω", "σώσω", "ἔσωσα", "σέσωκα", "σέσωσμαι, σέσωμαι", "ἐσώθην" },
    
    { 23, 189, CONSONANT_STEM_PERFECT_GAMMA, 8, "ἄγω", "ἄξω", "ἤγαγον", "ἦχα", "ἦγμαι", "ἤχθην" },
    { 24, 194, 0, 8, "ἥκω", "ἥξω", "", "", "", "" },
    
    { 25, 209, 0, 9, "ἀδικέω", "ἀδικήσω", "ἠδίκησα", "ἠδίκηκα", "ἠδίκημαι", "ἠδικήθην" },
    { 26, 215, 0, 9, "νῑκάω", "νῑκήσω", "ἐνῑ́κησα", "νενῑ́κηκα", "νενῑ́κημαι", "ἐνῑκήθην" },
    { 27, 223, 0, 9, "ποιέω", "ποιήσω", "ἐποίησα", "πεποίηκα", "πεποίημαι", "ἐποιήθην" },
    { 28, 225, 0, 9, "τῑμάω", "τῑμήσω", "ἐτῑ́μησα", "τετῑ́μηκα", "τετῑ́μημαι", "ἐτῑμήθην" },
    
    { 29, 229, CONSONANT_STEM_PERFECT_LAMBDA, 10, "ἀγγέλλω", "ἀγγελῶ", "ἤγγειλα", "ἤγγελκα", "ἤγγελμαι", "ἠγγέλθην" },
    { 30, 233, 0, 10, "ἀξιόω", "ἀξιώσω", "ἠξίωσα", "ἠξίωκα", "ἠξίωμαι", "ἠξιώθην" },
    { 31, 238, 0, 10, "δηλόω", "δηλώσω", "ἐδήλωσα", "δεδήλωκα", "δεδήλωμαι", "ἐδηλώθην" },
    { 32, 245, 0, 10, "καλέω", "καλῶ", "ἐκάλεσα", "κέκληκα", "κέκλημαι", "ἐκλήθην" },
    { 33, 246, 0, 10, "μένω", "μενῶ", "ἔμεινα", "μεμένηκα", "", "" },
    { 34, 257, 0, 10, "τελευτάω", "τελευτήσω", "ἐτελεύτησα", "τετελεύτηκα", "τετελεύτημαι", "ἐτελευτήθην" },
    
    { 35, 263, 0, 11, "ἀκούω", "ἀκούσομαι", "ἤκουσα", "ἀκήκοα", "", "ἠκούσθην" },
    
    { 36, 270, CONSONANT_STEM_PERFECT_CHI | PREFIXED, 11, "ἀποδέχομαι", "ἀποδέξομαι", "ἀπεδεξάμην", "", "ἀποδέδεγμαι", "" },
    { 37, 266, 0, 11, "βάλλω", "βαλῶ", "ἔβαλον", "βέβληκα", "βέβλημαι", "ἐβλήθην" },
    { 38, 267, 0, 11, "βούλομαι", "βουλήσομαι", "", "", "βεβούλημαι", "ἐβουλήθην" },
    { 39, 269, CONSONANT_STEM_PERFECT_CHI, 11, "δέχομαι", "δέξομαι", "ἐδεξάμην", "", "δέδεγμαι", "" },
    { 40, 279, CONSONANT_STEM_PERFECT_BETA, 11, "λαμβάνω", "λήψομαι", "ἔλαβον", "εἴληφα", "εἴλημμαι", "ἐλήφθην" },
    { 41, 283, 0, 11, "πάσχω", "πείσομαι", "ἔπαθον", "πέπονθα", "", "" },
    
    { 42, 324, PREFIXED, 12, "ἀνατίθημι", "ἀναθήσω", "ἀνέθηκα", "ἀνατέθηκα", "ἀνατέθειμαι", "ἀνετέθην" },
    { 43, 299, PREFIXED, 12, "ἀποδίδωμι", "ἀποδώσω", "ἀπέδωκα", "ἀποδέδωκα", "ἀποδέδομαι", "ἀπεδόθην" },
    { 44, 306, PREFIXED, 12, "ἀφίστημι", "ἀποστήσω", "ἀπέστησα, ἀπέστην", "ἀφέστηκα", "ἀφέσταμαι", "ἀπεστάθην" },
    { 45, 298, 0, 12, "δίδωμι", "δώσω", "ἔδωκα", "δέδωκα", "δέδομαι", "ἐδόθην" },
    { 46, 305, 0, 12, "ἵστημι", "στήσω", "ἔστησα, ἔστην", "ἕστηκα", "ἕσταμαι", "ἐστάθην" },
    { 47, 308, PREFIXED, 12, "καθίστημι", "καταστήσω", "κατέστησα, κατέστην", "καθέστηκα", "καθέσταμαι", "κατεστάθην" },
    { 48, 309, PREFIXED, 12, "καταλῡ́ω", "καταλῡ́σω", "κατέλῡσα", "καταλέλυκα", "καταλέλυμαι", "κατελύθην" },
    { 49, 323, 0, 12, "τίθημι", "θήσω", "ἔθηκα", "τέθηκα", "τέθειμαι", "ἐτέθην" },
    { 50, 325, 0, 12, "φιλέω", "φιλήσω", "ἐφίλησα", "πεφίληκα", "πεφίλημαι", "ἐφιλήθην" },
    { 51, 326, 0, 12, "φοβέομαι", "φοβήσομαι", "", "", "πεφόβημαι", "ἐφοβήθην" },
    
    { 52, 331, 0, 13, "γίγνομαι", "γενήσομαι", "ἐγενόμην", "γέγονα", "γεγένημαι", "" },
    { 53, 335, 0, 13, "ἔρχομαι", "ἐλεύσομαι", "ἦλθον", "ἐλήλυθα", "", "" },
    { 54, 339, 0, 13, "μανθάνω", "μαθήσομαι", "ἔμαθον", "μεμάθηκα", "", "" }, //LSJ: Pass., used by good writers only in pres
    { 55, 340, 0, 13, "μάχομαι", "μαχοῦμαι", "ἐμαχεσάμην", "", "μεμάχημαι", "" },
    { 56, 342, PREFIXED, 13, "μεταδίδωμι", "μεταδώσω", "μετέδωκα", "μεταδέδωκα", "μεταδέδομαι", "μετεδόθην" },
    { 57, 343, PREFIXED, 13, "μετανίσταμαι", "μεταναστήσομαι", "μετανέστην", "μετανέστηκα", "", "" },
    { 58, 345, 0, 13, "μηχανάομαι", "μηχανήσομαι", "ἐμηχανησάμην", "", "μεμηχάνημαι", "" },
    { 59, 356, 0, 13, "φεύγω", "φεύξομαι", "ἔφυγον", "πέφευγα", "", "" },
    
    { 60, 361, CONSONANT_STEM_PERFECT_KAPPA, 14, "δείκνῡμι", "δείξω", "ἔδειξα", "δέδειχα", "δέδειγμαι", "ἐδείχθην" },
    { 61, 364, PREFIXED, 14, "ἐπανίσταμαι", "ἐπαναστήσομαι", "ἐπανέστην", "ἐπανέστηκα", "", "" },
    { 62, 362, CONSONANT_STEM_PERFECT_KAPPA | PREFIXED, 14, "ἐπιδείκνυμαι", "ἐπιδείξομαι", "ἐπεδειξάμην", "", "ἐπιδέδειγμαι", "" },
    { 63, 365, 0, 14, "ἐρωτάω", "ἐρωτήσω", "ἠρώτησα", "ἠρώτηκα", "ἠρώτημαι", "ἠρωτήθην" },
    { 64, 372, 0, 14, "λανθάνω", "λήσω", "ἔλαθον", "λέληθα", "", "" },
    { 65, 377, PREFIXED, 14, "παραγίγνομαι", "παραγενήσομαι", "παρεγενόμην", "παραγέγονα", "παραγεγένημαι", "" },
    { 66, 378, PREFIXED, 14, "παραδίδωμι", "παραδώσω", "παρέδωκα", "παραδέδωκα", "παραδέδομαι", "παρεδόθην" },
    { 67, 379, PREFIXED, 14, "παραμένω", "παραμενῶ", "παρέμεινα", "παραμεμένηκα", "", "" },
    { 68, 382, 0, 14, "τυγχάνω", "τεύξομαι", "ἔτυχον", "τετύχηκα", "", "" },
    { 69, 384, PREFIXED, 14, "ὑπακούω", "ὑπακούσομαι", "ὑπήκουσα", "ὑπακήκοα", "", "ὑπηκούσθην" },
    { 70, 385, PREFIXED, 14, "ὑπομένω", "ὑπομενῶ", "ὑπέμεινα", "ὑπομεμένηκα", "", "" },
    { 71, 386, 0, 14, "φθάνω", "φθήσομαι", "ἔφθασα, ἔφθην", "", "", "" },
    { 72, 387, 0, 14, "χαίρω", "χαιρήσω", "", "κεχάρηκα", "", "ἐχάρην" },
    
    { 73, 388, 0, 15, "αἱρέω", "αἱρήσω", "εἷλον", "ᾕρηκα", "ᾕρημαι", "ᾑρέθην" },
    { 74, 389, 0, 15, "αἰσθάνομαι", "αἰσθήσομαι", "ᾐσθόμην", "", "ᾔσθημαι", "" },
    { 75, 420, CONSONANT_STEM_PERFECT_KAPPA | PREFIXED, 15, "διαφέρω", "διοίσω", "διήνεγκα, διήνεγκον", "διενήνοχα", "διενήνεγμαι", "διηνέχθην" },
    { 76, 395, 0, 15, "εἰμί", "ἔσομαι", "", "", "", "" },
    { 77, 396, 0, 15, "ἔστι(ν)", "ἔσται", "", "", "", "" },
    { 78, 397, PREFIXED, 15, "ἔξεστι(ν)", "ἐξέσται", "", "", "", "" },
    { 79, 398, 0, 15, "ἕπομαι", "ἕψομαι", "ἑσπόμην", "", "", "" },
    { 80, 404, CONSONANT_STEM_PERFECT_PI, 15, "ὁράω", "ὄψομαι", "εἶδον", "ἑόρᾱκα, ἑώρᾱκα", "ἑώρᾱμαι, ὦμμαι", "ὤφθην" },
    { 81, 421, CONSONANT_STEM_PERFECT_KAPPA | PREFIXED, 15, "συμφέρω", "συνοίσω", "συνήνεγκα, συνήνεγκον", "συνενήνοχα", "συνενήνεγμαι", "συνηνέχθην" },
    { 82, 419, CONSONANT_STEM_PERFECT_KAPPA, 15, "φέρω", "οἴσω", "ἤνεγκα, ἤνεγκον", "ἐνήνοχα", "ἐνήνεγμαι", "ἠνέχθην" },
    
    { 83, 423, PREFIXED, 16, "ἀναβαίνω", "ἀναβήσομαι", "ἀνέβην", "ἀναβέβηκα", "", "" },
    { 84, 422, 0, 16, "βαίνω", "-βήσομαι", "-ἔβην", "βέβηκα", "", "" },
    { 85, 424, CONSONANT_STEM_PERFECT_SIGMA, 16, "γιγνώσκω", "γνώσομαι", "ἔγνων", "ἔγνωκα", "ἔγνωσμαι", "ἐγνώσθην" },
    { 86, 439, PREFIXED, 16, "ἐκπῑ́πτω", "ἐκπεσοῦμαι", "ἐξέπεσον", "ἐκπέπτωκα", "", "" },
    { 87, 429, CONSONANT_STEM_PERFECT_GAMMA, 16, "λέγω", "ἐρῶ, λέξω", "εἶπον, ἔλεξα", "εἴρηκα", "εἴρημαι, λέλεγμαι", "ἐλέχθην, ἐρρήθην" },
    { 88, 434, CONSONANT_STEM_PERFECT_SIGMA, 16, "νομίζω", "νομιῶ", "ἐνόμισα", "νενόμικα", "νενόμισμαι", "ἐνομίσθην" },
    { 89, 438, 0, 16, "πῑ́πτω", "πεσοῦμαι", "ἔπεσον", "πέπτωκα", "", "" },
    { 90, 445, PREFIXED, 12, "προδίδωμι", "προδώσω", "προέδωκα, προύδωκα", "προδέδωκα", "προδέδομαι", "προεδόθην, προυδόθην" },
    { 91, 447, 0, 16, "φημί", "φήσω", "ἔφησα", "", "", "" },
    
    { 92, 449, 0, 17, "ἁμαρτάνω", "ἁμαρτήσομαι", "ἥμαρτον", "ἡμάρτηκα", "ἡμάρτημαι", "ἡμαρτήθην" },
    { 93, 452, CONSONANT_STEM_PERFECT_KAPPA, 17, "δοκέω", "δόξω", "ἔδοξα", "", "δέδογμαι", "-ἐδόχθην" },
    { 94, 454, 0, 17, "δύναμαι", "δυνήσομαι", "", "", "δεδύνημαι", "ἐδυνήθην" },
    { 95, 458, 0, 17, "εἶμι", "", "", "", "", "" },
    
    { 96, 460, CONTRACTED_FUTURE_ALPHA, 17, "ἐλαύνω", "ἐλῶ", "ἤλασα", "-ἐλήλακα", "ἐλήλαμαι", "ἠλάθην" },
    { 97, 461, 0, 17, "ἐπίσταμαι", "ἐπιστήσομαι", "", "", "", "ἠπιστήθην" },
    { 98, 463, 0, 17, "ἔχω", "ἕξω, σχήσω", "ἔσχον", "ἔσχηκα", "-ἔσχημαι", "" },
    
    { 99, 481, PREFIXED, 18, "ἀποθνῄσκω", "ἀποθανοῦμαι", "ἀπέθανον", "τέθνηκα", "", "" },
    { 100, 482, PREFIXED, 18, "ἀποκτείνω", "ἀποκτενῶ", "ἀπέκτεινα", "ἀπέκτονα", "", "" },
    { 101, 491, PREFIXED, 18, "ἀφῑ́ημι", "ἀφήσω", "ἀφῆκα", "ἀφεῖκα", "ἀφεῖμαι", "ἀφείθην" },
    { 102, 484, 0, 18, "βουλεύω", "βουλεύσω", "ἐβούλευσα", "βεβούλευκα", "βεβούλευμαι", "ἐβουλεύθην" },
    { 103, 485, PREFIXED, 18, "ἐπιβουλεύω", "ἐπιβουλεύσω", "ἐπεβούλευσα", "ἐπιβεβούλευκα", "ἐπιβεβούλευμαι", "ἐπεβουλεύθην" },
    { 104, 489, 0, 18, "ζητέω", "ζητήσω", "ἐζήτησα", "ἐζήτηκα", "", "ἐζητήθην" },
    { 105, 490, 0, 18, "ῑ̔́ημι", "-ἥσω", "-ἧκα", "-εἷκα", "-εἷμαι", "-εἵθην" },
    { 106, 493, 0, 18, "μέλλω", "μελλήσω", "ἐμέλλησα", "", "", "" },
    { 107, 496, 0, 18, "πιστεύω", "πιστεύσω", "ἐπίστευσα", "πεπίστευκα", "πεπίστευμαι", "ἐπιστεύθην" },
    { 108, 486, PREFIXED, 18, "συμβουλεύω", "συμβουλεύσω", "συνεβούλευσα", "συμβεβούλευκα", "συμβεβούλευμαι", "συνεβουλεύθην" },
    { 109, 492, PREFIXED, 18, "συνῑ́ημι", "συνήσω", "συνῆκα", "συνεῖκα", "συνεῖμαι", "συνείθην" },
    
    { 110, 500, CONSONANT_STEM_PERFECT_NU, 19, "αἰσχῡ́νομαι", "αἰσχυνοῦμαι", "", "", "ᾔσχυμμαι", "ᾐσχύνθην" },
    { 111, 512, PREFIXED, 19, "ἀποκρῑ́νομαι", "ἀποκρινοῦμαι", "ἀπεκρῑνάμην", "", "ἀποκέκριμαι", "" },
    { 112, 501, PREFIXED, 19, "ἀπόλλῡμι", "ἀπολῶ", "ἀπώλεσα, ἀπωλόμην", "ἀπολώλεκα, ἀπόλωλα", "", "" },
    
    { 113, 503, PREFIXED, 19, "", "ἀνερήσομαι", "ἀνηρόμην", "", "", "" },
    { 114, 502, 0, 19, "", "ἐρήσομαι", "ἠρόμην", "", "", "" },
    { 115, 504, 0, 19, "εὑρίσκω", "εὑρήσω", "ηὗρον", "ηὕρηκα", "ηὕρημαι", "ηὑρέθην" },
    { 116, 506, 0, 19, "ἡγέομαι", "ἡγήσομαι", "ἡγησάμην", "", "ἥγημαι", "ἡγήθην" },
    { 117, 511, 0, 19, "κρῑ́νω", "κρινῶ", "ἔκρῑνα", "κέκρικα", "κέκριμαι", "ἐκρίθην" },
    { 118, 518, 0, 19, "οἶδα", "εἴσομαι", "", "", "", "" },
    { 119, 519, PREFIXED, 19, "σύνοιδα", "συνείσομαι", "", "", "", "" },
    
    { 120, 529, CONSONANT_STEM_PERFECT_KAPPA | PREFIXED, 20, "ἀφικνέομαι", "ἀφίξομαι", "ἀφῑκόμην", "", "ἀφῖγμαι", "" },
    { 121, 530, 0, 20, "δεῖ", "δεήσει", "ἐδέησε(ν)", "", "", "" },
    { 122, 532, 0, 20, "κεῖμαι", "κείσομαι", "", "", "", "" },
    { 123, 534, CONSONANT_STEM_PERFECT_SIGMA, 20, "πυνθάνομαι", "πεύσομαι", "ἐπυθόμην", "", "πέπυσμαι", "" },
    { 124, 535, CONSONANT_STEM_PERFECT_PI, 20, "τρέπω", "τρέψω", "ἔτρεψα, ἐτραπόμην", "τέτροφα", "τέτραμμαι", "ἐτράπην, ἐτρέφθην" },
    { 125, 536, CONSONANT_STEM_PERFECT_NU, 20, "φαίνω", "φανῶ", "ἔφηνα", "πέφηνα", "πέφασμαι", "ἐφάνην" },
    { 126, 537, 0, 20, "χρή", "χρῆσται", "", "", "", "" }
};

Ending endings[NUM_ENDINGS] = {
    { 0, 2, 0, 0, 0, "ω", "εις", "ει", "ομεν", "ετε", "ουσι(ν)", "Present Active Indicative" },
    { 0, 2, 0, 0, 0, "ον", "ες", "ε(ν)", "ομεν", "ετε", "ον", "Imperfect Active Indicative" },
    { 0, 2, 0, 0, 0, "α", "ας", "ε(ν)", "αμεν", "ατε", "αν", "Aorist Active Indicative" },
    { 0, 3, 0, 0, 0, "α", "ας", "ε(ν)", "αμεν", "ατε", "ᾱσι(ν)", "Perfect Active Indicative" },
    { 0, 3, 0, 0, 0, "η", "ης", "ει(ν)", "εμεν", "ετε", "εσαν", "Pluperfect Active Indicative" },
    { 0, 2, 0, 0, 0, "ω", "εις", "ει", "ομεν", "ετε", "ουσι(ν)", "Future Active Indicative" },
    { 0, 3, 0, 0, 0, "ω", "ῃς", "ῃ", "ωμεν", "ητε", "ωσι(ν)", "Present Active Subjunctive" },
    { 0, 3, 0, 0, 0, "ω", "ῃς", "ῃ", "ωμεν", "ητε", "ωσι(ν)", "Aorist Active Subjunctive" },
    { 0, 3, 0, 0, 0, "οιμι", "οις", "οι", "οιμεν", "οιτε", "οιεν", "Present Active Optative" },
    { 0, 3, 0, 0, 0, "αιμι", "αις, ειας", "αι, ειε(ν)", "αιμεν", "αιτε", "αιεν, ειαν", "Aorist Active Optative" },
    { 0, 5, 0, 0, 0, "ομαι", "ει, ῃ", "εται", "ομεθα", "εσθε", "ονται", "Present Middle/Passive Indicative" },
    { 0, 5, 0, 0, 0, "ομην", "ου", "ετο", "ομεθα", "εσθε", "οντο", "Imperfect Middle/Passive Indicative" },
    { 0, 5, 0, 0, 0, "ην", "ης", "η", "ημεν", "ητε", "ησαν", "Aorist Passive Indicative" },
    { 0, 7, 0, 0, 0, "αμην", "ω", "ατο", "αμεθα", "ασθε", "αντο", "Aorist Middle Indicative" },
    { 0, 5, 0, 0, 0, "ῶ", "ῇς", "ῇ", "ῶμεν", "ῆτε", "ῶσι(ν)", "Aorist Passive Subjunctive" },
    { 0, 5, 0, 0, 0, "ειην", "ειης", "ειη", "εῖμεν, ειημεν", "εῖτε, ειητε", "εῖεν, ειησαν", "Aorist Passive Optative" },
    { 0, 7, 0, 0, 0, "ωμαι", "ῃ", "ηται", "ωμεθα", "ησθε", "ωνται", "Aorist Middle Subjunctive" },
    { 0, 7, 0, 0, 0, "αιμην", "αιο", "αιτο", "αιμεθα", "αισθε", "αιντο", "Aorist Middle Optative" },
    { 0, 5, 0, 0, 0, "μαι", "σαι", "ται", "μεθα", "σθε", "νται", "Perfect Middle/Passive Indicative" },
    { 0, 5, 0, 0, 0, "μην", "σο", "το", "μεθα", "σθε", "ντο", "Pluperfect Middle/Passive Indicative" },
    { 0, 5, 0, 0, 0, "ωμαι", "ῃ", "ηται", "ωμεθα", "ησθε", "ωνται", "Present Middle/Passive Subjunctive" },
    { 0, 5, 0, 0, 0, "οιμην", "οιο", "οιτο", "οιμεθα", "οισθε", "οιντο", "Present Middle/Passive Optative" },
    { 0, 11, 0, 0, 0, "", "ε", "ετω",   "", "ετε", "οντων", "Present Active Imperative" },
    { 0, 11, 0, 0, 0, "", "ου", "εσθω", "", "εσθε", "εσθων", "Present Middle/Passive Imperative" },
    { 0, 11, 0, 0, 0, "", "ον", "ατω",  "", "ατε", "αντων", "Aorist Active Imperative" },
    { 0, 11, 0, 0, 0, "", "αι", "ασθω", "", "ασθε", "ασθων", "Aorist Middle Imperative" },
    { 0, 11, 0, 0, 0, "", "ητι, ηθι", "ητω", "", "ητε", "εντων", "Aorist Passive Imperative" },
    { 0, 5, 0, 0, 0, "ομαι", "ει, ῃ", "εται", "ομεθα", "εσθε", "ονται", "Future Middle/Passive Indicative" },
    
    { 0, 9, 0, 0, 0, "ῶ", "ᾷς", "ᾷ", "ῶμεν", "ᾶτε", "ῶσι(ν)", "" },         //pres active indic a
    { 0, 9, 0, 0, 0, "ῶμαι", "ᾷ", "ᾶται", "ώμεθα", "ᾶσθε", "ῶνται", "" },   //pres mid/pass indic a
    { 0, 9, 0, 0, 0, "ων", "ᾱς", "ᾱ", "ῶμεν", "ᾶτε", "ων", "" },            //impf active indic a
    { 0, 9, 0, 0, 0, "ώμην", "ῶ", "ᾶτο", "ώμεθα", "ᾶσθε", "ῶντο", "" },     //impf mid/pass indic a
    { 0, 9, 0, 0, 0, "ῶ", "ᾷς", "ᾷ", "ῶμεν", "ᾶτε", "ῶσι(ν)", "" },         //pres active subj a
    { 0, 9, 0, 0, 0, "ῶμαι", "ᾷ", "ᾶται", "ώμεθα", "ᾶσθε", "ῶνται", "" },   //pres mid/pass subj a
    { 0, 9, 0, 0, 0, "ῷμι, ῴην", "ῷς, ῴης", "ῷ, ῴη", "ῷμεν, ῴημεν", "ῷτε, ῴητε", "ῷεν, ῴησαν", "" }, //pres active opt a
    { 0, 9, 0, 0, 0, "ῴμην", "ῷο", "ῷτο", "ῴμεθα", "ῷσθε", "ῷντο", "" },   //pres mid/pass opt a
    
    { 0, 9, 0, 0, 0, "ῶ", "εῖς", "εῖ", "οῦμεν", "εῖτε", "οῦσι(ν)", "" },         //pres active indic e
    { 0, 9, 0, 0, 0, "οῦμαι", "εῖ, ῇ", "εῖται", "ουμεθα", "εῖσθε", "οῦνται", "" },   //pres mid/pass indic e
    { 0, 9, 0, 0, 0, "ουν", "εις", "ει", "οῦμεν", "εῖτε", "ουν", "" },            //impf active indic e
    { 0, 9, 0, 0, 0, "ούμην", "οῦ", "εῖτο", "ούμεθα", "εῖσθε", "οῦντο", "" },     //impf mid/pass indic e
    { 0, 9, 0, 0, 0, "ῶ", "ῇς", "ῇ", "ῶμεν", "ῆτε", "ῶσι(ν)", "" },         //pres active subj e
    { 0, 9, 0, 0, 0, "ῶμαι", "ῇ", "ῆται", "ώμεθα", "ῆσθε", "ῶνται", "" },   //pres mid/pass subj e
    { 0, 9, 0, 0, 0, "οῖμι, οίην", "οῖς, οίης", "οῖ, οίη", "οῖμεν, οίημεν", "οῖτε, οίητε", "οῖεν, οίησαν", "" },//pres act opt e
    { 0, 9, 0, 0, 0, "οίμην", "οῖο", "οῖτο", "οίμεθα", "οῖσθε", "οῖντο", "" },   //pres mid/ass opt e
    
    { 0, 10, 0, 0, 0, "ῶ", "οῖς", "οῖ", "οῦμεν", "οῦτε", "οῦσι(ν)", "" },         //pres active indic o
    { 0, 10, 0, 0, 0, "οῦμαι", "οῖ", "οῦται", "ουμεθα", "οῦσθε", "οῦνται", "" },   //pres mid/pass indic o
    { 0, 10, 0, 0, 0, "ουν", "ους", "ου", "οῦμεν", "οῦτε", "ουν", "" },            //impf active indic o
    { 0, 10, 0, 0, 0, "ούμην", "οῦ", "οῦτο", "ούμεθα", "οῦσθε", "οῦντο", "" },     //impf mid/pass indic o
    { 0, 10, 0, 0, 0, "ῶ", "οῖς", "οῖ", "ῶμεν", "ῶτε", "ῶσι(ν)", "" },         //pres active subj o
    { 0, 10, 0, 0, 0, "ῶμαι", "οῖ", "ῶται", "ώμεθα", "ῶσθε", "ῶνται", "" },   //pres mid/pass subj o
    { 0, 10, 0, 0, 0, "οῖμι, οίην", "οῖς, οίης", "οῖ, οίη", "οῖμεν, οίημεν", "οῖτε, οίητε", "οῖεν, οίησαν", "" },//pres act opt o
    { 0, 9, 0, 0, 0, "οίμην", "οῖο", "οῖτο", "οίμεθα", "οῖσθε", "οῖντο", "" },   //pres mid/ass opt o
    
    { 0, 11, 0, 0, 0, "", "ᾱ", "ᾱ́τω",   "", "ᾶτε", "ώντων", "Present Active Imperative" }, //pres. active imper a
    { 0, 11, 0, 0, 0, "", "ῶ", "ᾱ́σθω", "", "ᾶσθε", "ᾱ́σθων", "Present Middle/Passive Imperative" }, //pres. mid/pass imper a
    { 0, 11, 0, 0, 0, "", "ει", "είτω",   "", "εῖτε", "ούντων", "Present Active Imperative" }, //pres. active imper e
    { 0, 11, 0, 0, 0, "", "οῦ", "είσθω", "", "εῖσθε", "είσθων", "Present Middle/Passive Imperative" }, //pres. mid/pass imper e
    { 0, 11, 0, 0, 0, "", "ου", "ούτω",   "", "οῦτε", "ούντων", "Present Active Imperative" }, //pres. active imper o
    { 0, 11, 0, 0, 0, "", "οῦ", "ούσθω", "", "οῦσθε", "ούσθων", "Present Middle/Passive Imperative" }, //pres. mid/pass imper o
    
    { 0, 10, 0, 0, 0, "μι", "ς", "σι(ν)", "μεν", "τε", "ᾱσι(ν)", "" },   //mi
    
    { 0, 10, 0, 0, 0, "οιμι, οιην", "οις, οιης", "οι, οιη", "οιμεν, οιημεν", "οιτε, οιητε", "οιεν, οιησαν", "" },//pres act opt o
    { 0, 10, 0, 0, 0, "", "ς", "τω", "", "τε", "ντων", "" },//mi aorist active imperatives
    { 0, 10, 0, 0, 0, "", "θι", "τω", "", "τε", "ντων", "" },//mi root aorist active imperatives
    
    { 0, 10, 0, 0, 0, "", "ο", "σθω", "", "σθε", "σθων", "Root Aorist Middle Imperative" },//mi root aorist middle imperatives
    { 0, 10, 0, 0, 0, "ν", "ς", "", "μεν", "τε", "σαν", "Root Aorist Indicative" },//mi root aorist indicative
    
    { 0, 11, 0, 0, 0, "", "οῦ", "εσθω", "", "εσθε", "εσθων", "Present Middle/Passive Imperative" }, //second aorist middle/passive imperatives
    { 0, 5, 0, 0, 0, "ειμην", "εῖο", "εῖτο, οῖτο", "ειμεθα, οιμεθα", "εῖσθε, οῖσθε", "εῖντο, οῖντο", "Present Middle/Passive Optative Tithemi" }, //Exception: H&Q page 347
    { 0, 9, 0, 0, 0, "ον", "ες", "ε", "ομεν", "ετε", "ον", "Imperfect Active Indicative" } //this is only for contracted verbs when decomposed so the nu moveable doesn't show up
};

