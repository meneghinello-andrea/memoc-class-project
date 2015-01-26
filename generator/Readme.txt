In questo file viene fornita una breve spiegazione su come
compilare ed eseguire il generatore di istanze relativo alla
prima parte del progetto di MEMOC.

##########################################################
					COMPILAZIONE
##########################################################
Per compilare correttamente il solver spostarsi, con il
terminale, all'interno della directory 'generator' e
lanciare il comando:

					make
					
##########################################################
					ESECUZIONE
##########################################################
Per eseguire il generatore accertarsi di aver eseguito
correttamente la compilazione e da terminale spostarsi
all'interno della cartella 'generator'.

Il solver necessita di parametri differenti in base al tipo
di generatore desiderato.

GENERATORE RANDOM parametri:

	param_1: tipologia di generatore -> RANDOM
	param_2: larghezza della piastra (nr intero)
	param_3: altezza della piastra (nr intero)
	param_4: numero di fori da istanziare (nr intero)
	
Il comando da lanciare è il seguente:

		./generator RANDOM param_2 param_3 param_4
		
GENERATORE CLUSTER parametri:

	param_1: tipologia di generatore -> CLUSTER
	param_2: larghezza della piastra (nr intero)
	param_3: altezza della piastra (nr intero)
	param_4: numero di cluster (nr intero)
	param_5: numero di fori da istanziare (nr intero)
	
Il comando da lanciare è il seguente:

		./generator CLUSTER param_2 param_3 param_4 param_5
		
GENERATORE CIRCLE parametri:

	param_1: tipologia di generatore -> CIRCLE
	param_2: larghezza della piastra (nr intero)
	param_3: altezza della piastra (nr intero)
	param_4: numero di fori da istanziare (nr intero)
	
Il comando da lanciare è il seguente:

		./generator CIRCLE param_2 param_3 param_4
		
Il generatore depositerà per ogni esecuzioni il file (.crd)
e (.dat) all'interno della cartella 'data'.
		
##########################################################
					PULIZIA
##########################################################
E' possibile da console pulire l'intero spazio di lavoro
attraverso il comando sempre all'interno della directory
'generator':

				make clean
				
ATTENZIONE però che tale comando rimuove la cartella

	'data'
	
è consigliabile effettuare un backup dei file in essa contenuti
se si desidera mantenere i risultati otteneuti.