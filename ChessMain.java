import javax.swing.*;
public class ChessMain	{
	public static void main(String args[])	{
		JFrame f=new JFrame("Shakti's Chess");
		f.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		UserInterface ui=new UserInterface();
		f.add(ui);
		f.setSize(500,500);
		f.setVisible(true);
	}
}