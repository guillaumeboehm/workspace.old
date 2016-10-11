import java.util.*;
import java.io.*;

public class Compte implements Serializable{
	private static String nom_proprietaire;
	private static long solde;

	public static void setNom(String nom){
		nom_proprietaire = nom;
	}

	public static String getNom(){ return nom_proprietaire; }

	public static void initSolde(){
		solde = 0;
	}

	public static void setSolde(long _solde){
		solde = _solde;
	}

	public static long getSolde(){
		return solde;
	}

	public static void afficher(){
		System.out.print(nom_proprietaire + " : ");
		System.out.println(solde);
	}
}