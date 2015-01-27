In questo file viene fornita una breve spiegazione su come
compilare ed eseguire il solver con l'algoritmo genetico
relativo alla prima parte del progetto di MEMOC.

##########################################################
					COMPILAZIONE
##########################################################
Per compilare correttamente il solver spostarsi, con il
terminale, all'interno della directory 'meta_heuristic' e
lanciare il comando:

					make
					
##########################################################
					ESECUZIONE
##########################################################
Per eseguire il solver accertarsi di aver eseguito
correttamente la compilazione e da terminale spostarsi
all'interno della cartella 'meta_heuristic'.

Il solver necessita di 3 parametri per essere eseguito:

	param_1: percorso al file .dat
	param_2: numero di elementi che compone la popolazione
	param_3: numero di evoluzioni da compiere
	
Il comando da lanciare è il seguente:

		./solver param_1 param_2 param_3
		
##########################################################
					PULIZIA
##########################################################
E' possibile da console pulire l'intero spazio di lavoro
attraverso il comando sempre all'interno della directory
'meta_heuristic'

				make clean
				
ATTENZIONE però che tale comando rimuove le cartelle

	'data'
	
è consigliabile effettuare un backup dei file in esse contenute
se si desidera mantenere i risultati otteneuti.