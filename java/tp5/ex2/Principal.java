import java.util.*;

public class Principal{
	private static Banque banque;
	public static void main(String[] arg){

		banque = new Banque();

		int choix;
		do{
			System.out.println("1 ajout 2 afficher tout 3 afficher 4 quitter");
			choix = Lire.i();
			switch(choix){

				case 1:
					ajouter();
					break;
				case 2:
					afficher_tous();
					break;
				case 3:
					afficher();
					break;
				case 4:
					break;


			}
		}
		while(choix != 4);
	}

	public static void afficher_tous(){
		banque.afficher();
	}

	public static void afficher(){
		System.out.println("Entrez le nom du compte :");
		String nom = Lire.S();
		banque.afficher(nom);
	}

	public static void ajouter(){
		String nom;
		System.out.println("Entrez le nom du nouveau compte :");
		nom = Lire.S();
		banque.ajoutCompte(nom);
	}
}