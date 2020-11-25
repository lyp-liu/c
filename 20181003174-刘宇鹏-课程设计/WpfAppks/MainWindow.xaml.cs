using System;
using System.Collections.Generic;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Forms;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;

namespace WpfAppks
{
    /// <summary>
    /// MainWindow.xaml 的交互逻辑
    /// </summary>
    public partial class MainWindow : Window
    {
        public MainWindow()
        {
            InitializeComponent();
        }
        private string pathname = string.Empty;
        bool b = false;
        float pointX = 0.0F;
        float pointY = 0.0F;
        float pointX1 = 0.0F;
        float pointY1 = 0.0F;
        private void Button1_Click(object sender,EventArgs e)
        {
            //打开图片
            OpenFileDialog file = new OpenFileDialog();
            file.InitialDirectory = ".";
            file.Filter = "PNG文件(*.png)|*.png|位图文件(*.bmp)|*.bmp|JPG文件(*.jpg)|*.jpg|所有文件(*.*)|*.*";
            file.ShowDialog();
            if (file.FileName != string.Empty)
            {
                try
                {
                    pathname = file.FileName;   //获得文件的绝对路径
                    this.pictureBox1.Load(pathname);
                }
                catch (Exception ex)
                {
                    System.Windows.Forms.MessageBox.Show(ex.Message);
                }
            }
        }

        private void Button2_Click(object sender, EventArgs e)
        {
            //弹出字体设置对话框
            //需要通过事件调用该控件的 ShowDialog 方法显示对话框
            FontDialog fontDialog1 = new FontDialog();
            fontDialog1.ShowApply = true;//应用按钮
            fontDialog1.ShowColor = true;//显示颜色选择
            System.Windows.Forms.DialogResult dr = fontDialog1.ShowDialog();

            //如果在对话框中单击“确认”按钮，则更改文本框中的字体

            if (dr == System.Windows.Forms.DialogResult.OK)

            {

                richTextBox1.Font = fontDialog1.Font;//将选择的字体类型应用到richtextbox中
                richTextBox1.ForeColor = fontDialog1.Color;//将选择的字体颜色应用到richtextbox中

            }
        }

        private void Button3_Click(object sender, EventArgs e)
        {
            //图片保存对话框
           /* //g对原始图片进行操作
            Graphics g = Graphics.FromImage(this.pictureBox1.Image);
            pointX = pictureBox1.Image.Width / 2;
            pointY = pictureBox1.Image.Height / 2;
            PointF drawpoint = new PointF(pointX, pointY);
            Font drawFont = richTextBox1.Font;
            SolidBrush drawBrush = new SolidBrush(richTextBox1.ForeColor);
            g.DrawString("hello world",drawFont,drawBrush, drawpoint);*/
            SaveFileDialog save = new SaveFileDialog();
            save.InitialDirectory = ".";
               // System.Windows.Forms.Application.StartupPath ;
            
            save.AddExtension = true;
            save.Filter = "PNG文件(*.png)|*.png|位图文件(*.bmp)|*.bmp|JPG文件(*.jpg)|*.jpg|所有文件(*.*)|*.*";
            //save.FileName = "temp";
            save.ShowDialog();
            if (save.FileName != string.Empty)
            {
                Bitmap bm = new Bitmap(pictureBox1.Image);
                bm.Save(save.FileName);
                //pictureBox1.Image.Save(save.FileName);
            }
        }

        private void PictureBox1_Paint(object sender, PaintEventArgs e)
        {
            //重写picturebox的OnPaint方法
            if (b == false)//鼠标未点击前未false不重新绘制
                return;
            string str = richTextBox1.Text;//获取richtextbox中的文字
            //g对原始图片进行操作
            Graphics g = Graphics.FromImage(this.pictureBox1.Image);
            //gl对picturebox控件上画布图片进行操作
            Graphics gl = e.Graphics;
            // Create font and brush.
            Font drawFont = richTextBox1.Font;
            SolidBrush drawBrush = new SolidBrush(richTextBox1.ForeColor);
            //创建用于绘制文本的左上角的点。
            //drawpoint1为picturebox控件上鼠标点击的坐标
            //drawpoint为图像上经过比例变换对应的像素点坐标
            PointF drawpoint = new PointF(pointX, pointY);
            PointF drawpoint1 = new PointF(pointX1, pointY1);
            g.DrawString(str, drawFont, drawBrush, drawpoint);
            gl.DrawString(str, drawFont, drawBrush, drawpoint1);
        }

        private void PictureBox1_MouseDown(object sender, System.Windows.Forms.MouseEventArgs e)
        {
            //获得图片的宽度和高度
            int p_width = pictureBox1.Image.Width;
            int p_height = pictureBox1.Image.Height;
            pointX1 = (float)e.X;
            pointY1 = (float)e.Y;
            pointX = pointX1/pictureBox1.Width*p_width;
            pointY = pointY1/pictureBox1.Height*p_height;
            b = true;
            //重绘picturebox
            pictureBox1.Refresh();
        }
    }
}
