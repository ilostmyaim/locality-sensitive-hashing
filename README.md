# Tsob

Ανάπτυξη Λογισμικού για Αλγοριθμικά
Προβλήματα 2018-2019
Όνομα: Γεώργιος
Επώνυμο: Τσομπανέλης
ΑΜ: 1115201400213

Μέρος 1


Το παραδοτέο αποτελείται από τα παρακάτω αρχεία πηγαίου κώδικά:
1)cube.cpp ,το οποίο είναι υπεύθυνο για την εκτέλεση του υπερκύβου.

2)lsh.cpp,το οποίο είναι υπεύθυνο για τη εκτέλεση του LSH.

3)CUBE.cpp, περιέχει τον constructor της class CUBE ,τη συνάρτηση
executeCUBE που είναι υπεύθυνη για την εισαγωγή των vectors στη δομή
και την εκτέλεση των ερωτημάτων (queries), τη συνάρτηση displayCUBE
που τυπώνει ολόκληρη τη δομή του υπερκύβου με ένα γραφικά κατανοητό τρόπο, τη rangeSearch που είναι υπεύθυνη για την υλοποίηση του αλγορίθμου range, τη nearestNeighbor που βρίσκει τον κοντινότερο γείτονα καθώς και τον approximate NN και τέλος την initParametersCube που διαβάζει τις παραμέτρους από τη γραμμή εντολών και αρχικοποεί τις κατάλληες μεταβλητές.

4)LSH.cpp ,όμοια με το CUBE.cpp περιέχει τις αντίστοιχες συναρτήσεις.

5)hash.cpp: περιέχει τον constructor της class Hash η οποία ουσιαστικά περιέχει τον πίνακα κατακερματισμού(κάθε bucket αποτελεί μία λίστα της STL ώστε αν αντιμετωπίζονται τα collisions και κάθε κόμβος της λίστας περιέχει το id του εκάστοτε vector και το ίδιο το vector).
	Η συνάρτηση traverseBucket εκτελεί τον αλγόριθμο range search  και τυπώνει όλα τα items ,δηλαδή τα ids των vectors εντός του range σύμφωνα με την απαίτηση της εκφώνησης της άσκησης.
	Η συνάρτηση nearestNeighborTraverse βρίσκει τον κοντινότερο γείτονα και τον approximate NN ,με βάση κάποιο approximation factor εντός του (0,1), και τυπώνει αυτούς.Επιστρέφει το ratio app_distance/min_distance για την εύρεση του MAX ratio στο τέλος εκτέλεσης του προγράμματος.
	Η displayHash() τυπώνει κάποιο hashTable.
	Οι συναρτήσεις euclideanNorm,cosineSimilarity υλοποιούν τις τις ανάλογες μετρικές για την εύρεση της απόστασης μεταξύ δύο διανυσμάτων.
	Η innerProduct υπολογίζει το εσωτερικό γινόμενο δύο διανυσμάτων.
	Η hash  δημιουργεί μία συνάρτηση φ σύμφωνα με τη θεωρία χρησιμοποιώντας τις κατάλληλες h.Επιστρέφει τη hash value.
	Η cosineHash εκτελεί την ίδια λειτουργία με τη hash ,αλλά για την ευκλείδια μετρική , όπως αναγράφεται στο pdf της θεωρίας.Επιστρέφει τη hash value που έχει κατασκευάσει από το bitstring που έχει προκύψει.

	Η συνάρτηση hashCube υλοποιεί το hashing για το hypercube και την ευκλείδια νόρμα. Μετατρέπει τις τιμές των h functions σε 0-1 ,ελέγχοντας  πάντα αν η προκύπτουσα τιμή της h έχει ήδη υπολογισθεί ,οπότε και έχει ήδη αντιστοιχηθεί σε 0 ή 1. 


Header files:
1)CUBE.h: περιέχει τον ορισμό για την κλάση CUBE για το hypercube.

2)LSH.h: περιέχει την κλάση LSH για το lsh.

3)hash.h: περιέχει την κλάση Hash και τις δηλώσεις των συναρτήσεων για τον υπολογισμό της euclidean norm, cosine similarity ,εσωτερικού γινομένου και print_vector που τυπώνει ένα vector.

Επίσης περιέχεται Makefile.


Μεταγλώττιση:
Πραγματοποιείται μέσω της απλής εντολής make.

Εκτέλεση:
Για το lsh:
./lsh -d <input_file> -k <int> -L <int> -q <query_file> -o <output_file> -metric <name_of_metric>

Για το hypercube:
./cube -d <input_file> -k <int> -M <int> -q <query_file> -o <output_file> -metric <name_of_metric> -probes <int>

Η μετρική δίνεται σαν παράμετρος από τη γραμμή εντολών, αν δε δοθεί χρησιμοποείται η ευκλείδια.

Ακολουθούν αποτελέσματα ενδεικτικών εκτελέσεων των lsh και cube.

HyperCube με ευκλείδια μετρική και input file το siftsmall:
Nearest Neighbor
Execution 1
k = 8
M = 10
probes = 2
tLSH: 0.008226645
tTrue: 0.008235545
avg time = 0.0063 seconds
Max Ratio = 2.254201181

Execution 2
k = 11
M = 10
probes = 5
tLSH: 0.003442108
tTrue: 0.003453219
avg time = 0.002262395 seconds
Max Ratio = 4.130222179

Execution 3
k = 11
M = 10
probes = 30
tLSH: 0.002496400
tTrue: 0.002765179
avg time = 0.002428592 seconds
Max Ratio = 4.223077484

Range Search
Execution 1(radius = 250)
k = 11
M = 10 
probes = 20
total execution time: 2.94861448

Execution 2(radius = 350)
k = 11
M = 10
probes = 20
total execution time: 3.274141

Cosine similarity
Nearest Neighbor:
Execution 1
k = 8
M = 10
probes = 2
tLSH: 0.000996600
tTrue: 0.001355678
avg time = 0.00066 seconds
Max Ratio = 2.254201181

Execution 2
k = 11
M = 10
probes = 5
tLSH: 0.000996600
tTrue: 0.000998678
avg time = 0.00066 seconds
Max Ratio = 4.668760228
total execution time: 0.265715669

Execution 3
k = 8
M = 10
probes = 50
tLSH: 0.000005261
tTrue: 0.000005378
avg time = 0.000005221 seconds
Max Ratio = 4.878960338
total execution time: 0.108677343

Range Search
Execution 1(radius 0.5)
k = 8
M = 10
probes = 5
total execution time: 4.29471566

Execution 2(radius 0.2)
k = 8
M = 10
probes = 5
total execution time: 0.977711613



LSH με ευκλείδια μετρική και input file το siftsmall:
Nearest Neighbor

Execution 1
k = 4
L = 5
tLSH: 0.000042676
tTrue: 0.000043007
avg time = 0.00004531 seconds
total execution time: 0.0326497212
Max Ratio = 2.880821381




Execution 2
k = 6
L = 6
tLSH: 0.000020930
tTrue: 0.000021541
avg time = 0.00002241 seconds
total execution time: 0.034217970
Max Ratio = 2.764421052

Execution 3
k = 4
L = 6
tLSH: 0.000037161
tTrue: 0.000037379
avg time = 0.00003522 seconds
total execution time: 0.034217970
Max Ratio = 3.101399937

Cosine similarity:
Execution 1
k = 4
L = 5
tLSH: 0.000072572
tTrue: 0.000072707
avg time = 0.00007422 seconds
total execution time: 0.0726597335
Max Ratio = 4.997094335

Execution 2
k = 4
L = 6
tLSH: 0.000088672
tTrue: 0.000088720
avg time = 0.000089231 seconds
total execution time: 0.077260342
Max Ratio = 4.907507766

Range Search

Euclidean
Execution 1(radius 250)
k = 4
L = 5
total execution time = 0.022944809

Execution 2(radius 350)
k = 4
L = 5
total execution time = 0.026213658

Cosine Similarity
Execution 1(radius 0.2)
k = 4
L = 5
total execution time = 3.2683996

Execution 2(radius 0.3)
k = 4
L = 5
total execution time = 6.05999407

Execution 3(radius 0.5)
k = 4
L = 5
total execution time = 5.75637204
