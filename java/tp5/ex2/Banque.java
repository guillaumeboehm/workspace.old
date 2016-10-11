import java.util.*;
import java.io.*;

public class Banque implements Serializable{
	private static Vector<Compte> comptes;

	public Banque(){
		comptes = new Vector<Compte>();
	}

	public static void ajoutCompte(String nom){
		Compte compte_temp = new Compte();
		compte_temp.setNom(nom);
		compte_temp.initSolde();
		comptes.addElement(compte_temp);
	}

	public static void afficher(){
		for(int i=0; i<comptes.size(); ++i){
			comptes.elementAt(i).afficher();
		}
		comptes.elementAt(1).afficher();
	}

	public static void afficher(String nom){
		boolean found = false;
		for(int i=0; i<comptes.size(); ++i){
			if(comptes.elementAt(i).getNom().equals(nom)){
				comptes.elementAt(i).afficher();
			}
		}
	}
}