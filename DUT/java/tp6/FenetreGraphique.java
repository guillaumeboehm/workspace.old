import javax.swing.*;

public class FenetreGraphique extends JFrame{
	public ZoneDessin zoneDessin;

	public FenetreGraphique(String s){
		super(s);
		setSize(800,800);
		setLocationRelativeTo(null);
		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		setResizable(false);
		setAlwaysOnTop(true);
		
		zoneDessin = new ZoneDessin();
		setContentPane(zoneDessin);

		setVisible(true);
	}


}