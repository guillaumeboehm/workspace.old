import java.util.*;
import java.io.File;

public class Repertoire{

	public static void main(String[] arg){
		
		File rep;
		String rep_name;

		do{
			System.out.println("Entrez le nom du répertoire à parcourrir :");
			rep_name = Lire.S();
			rep = new File(rep_name);
			if(!rep.isDirectory()) System.out.println("introuvable");
		}
		while(!rep.isDirectory());

		String[] rep_list = rep.list();

		System.out.println("");
		File file_temp;
		int file_count = 0;
		int dir_count = 0;
		long rep_size = 0;
		for(int i=0; i<rep_list.length; ++i){
			file_temp = new File(rep_list[i]);
			System.out.print(file_temp.getName() + " ");
			System.out.print("\u001B[33m" + file_temp.length() + "\u001B[0m" + " ");
			rep_size = file_temp.length();
			if(file_temp.isDirectory()){
				System.out.print("\u001B[31mDir\u001B[0m");
				dir_count = dir_count+1;
			}
			else
				file_count = file_count + 1;
			System.out.println("");
		}
		System.out.println("il y a \u001B[32m" + file_count + " fichier(s)\u001B[0m dans ce repertoire et \u001B[31m" + dir_count + " dossier(s)\u001B[0m occupant \u001B[33m" + rep_size + " octets\u001B[0m.");
	}
}