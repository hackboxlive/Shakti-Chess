import java.awt.*;
import java.awt.event.*;
import javax.swing.*;
public class UserInterface extends JPanel implements MouseListener, MouseMotionListener	{
	static int x=0,y=0;
	static int squareSize=50;
	@Override
	public void paintComponent(Graphics g)	{
		super.paintComponent(g);
		this.setBackground(Color.GRAY);
		this.addMouseListener(this);
		this.addMouseMotionListener(this);
		for(int i=0;i<64;i+=2)	{
			g.setColor(new Color(255,200,100));
			g.fillRect((i%8+(i/8)%2)*squareSize,(i/8)*squareSize,squareSize,squareSize);
			g.setColor(new Color(150,50,30));			
			g.fillRect(((i+1)%8-((i+1)/8)%2)*squareSize,((i+1)/8)*squareSize,squareSize,squareSize);
		}
//		g.setColor(Color.WHITE);
//		g.fillRect(x,y,20,20);
//		g.setColor(Color.BLACK);
//		g.fillRect(40,20,20,20);
//		g.drawString("Shakti",50,50);
//		Image chessPiecesImage=new ImageIcon("ChessPieces.png").getImage();
//		g.drawImage(chessPiecesImage,x,y,x+64,y+64,0,0,64,64,this);
	}
	@Override
	public void mouseMoved(MouseEvent e)	{}
	@Override
	public void mousePressed(MouseEvent e)	{}
	@Override
	public void mouseReleased(MouseEvent e)	{}
	@Override
	public void mouseClicked(MouseEvent e)	{
		x=e.getX();
		y=e.getY();
		repaint();
	}
	@Override
	public void mouseDragged(MouseEvent e)	{}
	@Override
	public void mouseEntered(MouseEvent e)	{}
	@Override
	public void mouseExited(MouseEvent e)	{}
}