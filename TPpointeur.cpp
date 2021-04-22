#include<stdio.h>
#include<malloc.h>
#include<string.h>
typedef struct{int ref;char marque[20];char type[20];int qtt;float prixht;}voiture;
typedef struct cellule{voiture val;struct cellule*suiv;}cellule;
typedef cellule* point;
void ajout(point *tete,voiture x){
	point r;
	r=(cellule*)malloc(sizeof(cellule));
	(*r).val=x;
	(*r).suiv=*tete;
	*tete=r;
}
point rech(point tete ,int rf){
		point p;
	p=tete;
	while((p!=NULL)&&((*p).val.ref!=rf)){
			p=(*p).suiv;
	}
	return p;
}
void affvoiture(point tete){
	int ref;
	printf("donner le reference du voiture a chercher:\n");
	scanf("%d",&ref);
	point p=rech(tete,ref);
	if(p!=NULL)printf("reference	:%d\nmarque	:%s\ntype	:%s\nquantite	:%d\nprixHT	:%.3f\n",(*p).val.ref,(*p).val.marque,(*p).val.type,(*p).val.qtt,(*p).val.prixht);
		else printf("pas de reference!!!");
}
void afftoutvoiture(point tete){
	point p;
	p=tete;
	while(p!=NULL){
		printf("reference	:%d\nmarque		:%s\ntype		:%s\nquantite	:%d\nprixHT		:%.3f\n",(*p).val.ref,(*p).val.marque,(*p).val.type,(*p).val.qtt,(*p).val.prixht);
		p=(*p).suiv;
	}
}
void modprix(point tete){
	int ref;
	point p;
	float prix;
	printf("donner la reference du voiture:\n");
	scanf("%d",&ref);
	p=rech(tete,ref);
	if(p!=NULL) {
		printf("l'ancien prix hors taxes egale:	%f\ndonner le nouveaux:\n ",(*p).val.prixht);
		scanf("%.3f",&prix);
		(*p).val.prixht=prix;
	}else printf("pas de reference !!!!");
}
void recup (point *tete){
	FILE *g;
	voiture v;
	g=fopen("Parc.bin","r");
	if(g!=NULL){
		while(!feof(g)){
			fread(&v,sizeof(voiture),1,g);
			if(!feof(g))
			ajout(tete,v);
		}	
	}
	fclose(g);
}
void save (point tete){
	FILE *g;
	g=fopen("Parc.bin","w");
	point p=tete;
	while(p!=NULL){
		fwrite(&((*p).val),sizeof(voiture),1,g);
		p=(*p).suiv;
	}
	fclose(g);
}
void achat(point tete){
	int ref ;
	point p;
	int choix;
	printf("donner la voiture que vous voulez acheter:\n");
	scanf("%d",&ref);
	p=rech(tete,ref);
	if(p!=NULL){
		float x=(*p).val.prixht*1.22;
		printf("le prix final de la voiture egale a	:%f\nvoulez vous la acheter? \n1:oui	0:non\n",x);
		scanf("%d",&choix);
		if (choix==1){
			if ((*p).val.qtt>0){
				(*p).val.qtt-=1;
				printf("achat validee :)");
			}else printf("quantite insuffisante");
		}else printf ("achat non valide :|");
	}else printf("reference introuvable!!!");
}
int main(){
	point tete=NULL;
	int choix;
	voiture x;
	recup(&tete);
	do{
		printf("\n****************************************\n");
		printf("*1=>pour ajouter une voiture:            *\n");
		printf("*2=>pour afficher une seule voiture:     *\n");
		printf("*3=>pour afficher toute les voiture:     *\n");
		printf("*4=>pour modifier le prix d'une voiture: *\n");
		printf("*5=>pour acheter une voiture:            *\n");
		printf("*6=>pour quitter:                        *\n");
		scanf("%d",&choix);
		printf("\n****************************************\n");
		switch(choix){
			case 1:
				printf("donner la reference de la voiture:\n");
				scanf("%d",&x.ref);
				if (!rech(tete,x.ref)){
					printf("donner la marque de la voiture:\n");
					scanf("%s",&x.marque);
					printf("donner le type de la voiture:\n");
					scanf("%s",&x.type);
					printf("donner la quantite en stock:\n");
					scanf("%d",(&x.qtt));
					printf("donner le prix hors taxe:\n");
					scanf("%f",&x.prixht);
					ajout(&tete,x);
					}else printf("cette voiture existe");
					break;
			case 2:affvoiture(tete);break;
			case 3:afftoutvoiture(tete);break;
			case 4:modprix(tete);break;
			case 5:achat(tete);break;
			case 6:printf("fin dinstruction!!");	
		}
	}while(choix!=6);
	save(tete);
}
