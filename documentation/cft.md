### Transferts  dans un état donné ?
    CFTUTIL listcat state=K

### Etat d'un fichier
    CFTUTIL LISTCAT   part=SAFAR,idf=IDFIC1

###  Lister les fichiers envoyé vers un partenaire
    CFTUTIL listcat part=SAFAR
	
### Files in Error
    CFTUTIL LISTCAT  STATE=H

### Logs
    cftlog

### Errors
    001 à 499: anomalie locale
    500 à 999: anomalie du partenaire
    110 fichier local inexistant
    610 fichier distant inexistant	

### Les fichiers envoyés

    cftutil listcat or cftcatab

	Les types sont :
	F	File
	M	Message
	R	reply
	Les types peuvent être :
	S	Send
	R	Receive
	La colonne DTSA nous donne l'état des transferts:
	D :	Fichier en attente des transferts
	C:	Fichier en cours de transfert
	H :	Fichier non reçu (H pour HOLD), le fichier n'a pas été mis à disposition
	K :	Fichier non envoyé (K pour KEEP), le partenaire n'a pas déclenché l'émission
	T :	Fichier ayant eu un problème d'exécution de procédure de fin de transfert ou n'ayant pas de procédure de fin de transfert
	X :	Transfert réalisé et procédure de fin de transfert exécutée (X pour eXecute)	

### Docs
- http://wiki.tuxunix.com/index.php/Doc_CFT
- http://jlbicquelet.free.fr/produits/cft/cft_faq.php#fichiers3

