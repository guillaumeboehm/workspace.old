import java.awt.*;
import java.util.*;
import javax.swing.*;
import java.io.File;
import javax.imageio.ImageIO;
import java.io.IOException;

public class ZoneDessin extends JPanel{
	private Image img;

	public ZoneDessin(){
		try{
			img = ImageIO.read(new File("tux.png"));
		}
		catch(IOException e){
			e.printStackTrace();
		}
	}

	public void paint(Graphics g){
		mandelbrot(g);
	}

	public void mandelbrot(Graphics g){

        //la couleur
        g.setColor(Color.black);
         
        //les bornes de la fractale
        double x1=-2.11;
        double x2=0.6;
        double y1=-1.2;
        double y2=1.2;
        double px = -0.1011;
        double py = 0.9563;
         
        //zoom, taille de la zone ou on va dessiner la fractale
        long nb = 0;//le nb de fois que la valeur max des int a été passé
        long valeur = 3000;

        //long.MAX_VALUE
         
        //zoom = nb*long.MAX_VALUE + (valeur%long.MAX_VALUE)

        valeur = Lire.l()%;

        //le nombre d'itération
        int iter_max=200;
        
         
        double z_r,z_i,c_r,c_i;
        Color color_i=Color.black;
        //calcul
        for(int x=-this.getSize().width/2;x<this.getSize().width/2;x++){
            
            for(int y=-this.getSize().height/2;y<this.getSize().height/2;y++){
                z_r=0;
                z_i=0;
                 
                c_r=(double)x/(nb*long.MAX_VALUE + valeur) + px;
                c_i=(double)y/(nb*long.MAX_VALUE + valeur) + py;
                 
                int i=0;
                 
                do{
                    double tmp = z_r;
                    z_r = z_r*z_r - z_i*z_i +c_r;
                    z_i = 2*z_i*tmp +c_i;
                    i = i+1;
                }while(z_r*z_r + z_i*z_i < 4 && i < iter_max);
                 
                //allumer pixel
            	if(i<=99)
            		color_i = new Color(0,(int)(i*2.55),0);
                else
                	color_i = new Color(0,0,0);
                g.setColor(color_i);
                g.drawLine(x+this.getSize().width/2,y+this.getSize().height/2,x+this.getSize().width/2,y+this.getSize().height/2);
            }
        }
    }
}