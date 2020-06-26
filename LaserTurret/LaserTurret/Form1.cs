using System;
using System.Drawing;
using System.Windows.Forms;
using System.Diagnostics;

namespace LaserTurret
{
    public partial class Form1 : Form
    {
        public Stopwatch watch {get; set;}
        public Form1()
        {
            InitializeComponent();
        }
        
        
        private void Form1_Load(object sender, EventArgs e)
        {
            watch = Stopwatch.StartNew();
            port.Open(); //open serial port to communicate with the arduino
        }
        
        //send serial data when the mouse moves on form1
        private void Form1_MouseMove(object sender, MouseEventArgs e)
        {
            writeToPort(new Point(e.X, e.Y));   //pass event data
        }
        public void writeToPort(Point coordinates) //set up write data for arduino
        {
            if (watch.ElapsedMilliseconds > 15)     //limits amount of serial data being sent to every 15ms, relsoving latencey issue 
            {
                watch = Stopwatch.StartNew();
                port.Write(String.Format("X{0}Y{1}",            //format xy coordinates using string
                (180 -coordinates.X / (Size.Width / 180)),      //scales data X: divides the X coordinate by the width of the form over the angle of rotation of the servo 
                (180 - coordinates.Y / (Size.Height / 180))));  //data Y: divides Y coordinate by the height of the form over the angle of rotation of the servo
                
                //due to the orientation of the servos, the turret moved opposite to the movement of the mouse
                //Therefore, I added "180 -" to invert the direction resolving the issue
            }
         }
       
    }
}
