   M S B A M L   `   `   `  ����^  ZWindowsFormsIntegration, Version=4.0.0.0, Culture=neutral, PublicKeyToken=31bf3856ad364e35tOclr-namespace:System.Windows.Forms.Integration;assembly=WindowsFormsIntegration System.Windows.Forms.Integration  5   	   [ WSystem.Windows.Forms, Version=4.0.0.0, Culture=neutral, PublicKeyToken=b77a5c561934e089Y@clr-namespace:System.Windows.Forms;assembly=System.Windows.FormsSystem.Windows.Forms 5   	   C ?WpfAppks, Version=1.0.0.0, Culture=neutral, PublicKeyToken=null#clr-namespace:WpfAppksWpfAppks 5   	      WpfAppks.MainWindow   5   	   _WinFormHostOclr-namespace:System.Windows.Forms.Integration;assembly=WindowsFormsIntegration  5   	   TWinFormControls@clr-namespace:System.Windows.Forms;assembly=System.Windows.Forms  5   	   W SPresentationCore, Version=4.0.0.0, Culture=neutral, PublicKeyToken=31bf3856ad364e35R NWindowsBase, Version=4.0.0.0, Culture=neutral, PublicKeyToken=31bf3856ad364e35\ XPresentationFramework, Version=4.0.0.0, Culture=neutral, PublicKeyToken=31bf3856ad364e35F 9http://schemas.microsoft.com/winfx/2006/xaml/presentation      5   	   R NSystem.Xaml, Version=4.0.0.0, Culture=neutral, PublicKeyToken=b77a5c561934e089:x,http://schemas.microsoft.com/winfx/2006/xaml     5   	   @d2http://schemas.microsoft.com/expression/blend/2008     5   	   Jmc;http://schemas.openxmlformats.org/markup-compatibility/2006     5   	   (localclr-namespace:WpfAppks     5   	     � Title$  向图像中添加文字��5
   	   $��510.6��6   $	��710��6)   .��5      � $��
0,0,-6.4,6q�6   .+�5   
   7   1System.Windows.Forms.Integration.WindowsFormsHost  $
��Left=�6   $��40��66   $��725,370,-0.4,0q�6B   $	��Top=�6Z   $��69��6r     5   
   -   5        $��windowsFormsHost1��5   V   $��42��6   $
��Left=�6'   $��
10,326,0,0q�6B   $	��Top=�6o   $	��110��6�      Child. 5      !  System.Windows.Forms.Button  -   5        button1��%  System.Windows.Forms.ButtonBase   Text$ 浏览图像��5   6   "  System.Windows.Forms.Control   Width$	 150��6X   5        5   
   -   5        $��windowsFormsHost2��5   V   $��42��6   $
��Left=�6'   $��
10,377,0,0q�6B   $	��Top=�6o   $	��110��6�   . 5        -   5        button2��$ 设置文字��5   6   $	 150��6X   5        5   
   -   5        $��windowsFormsHost3��5   V   $��42��6   $
��Left=�6'   $��
10,430,0,0q�6B   $	��Top=�6o   $	��110��6�    J� RenderTransformOrigin$ 
0.41,1.347&�6�   . 5        -   5        button3��$ 保存图像��5   6   $	 150��6X   5        5   
   -   5        $��windowsFormsHost4��5   X   $	��183��6   $
��Left=�6(   $��148,283,0,0q�6C   $	��Top=�6q   $	��478��6�   . 5      &   System.Windows.Forms.RichTextBox  -   5        richTextBox1��   Text$  ��5   @   $	 150��6H   5        5   
   -	   5        $��windowsFormsHost5��5   V   $	��252��6   $
��Left=�6(   $��	10,15,0,0q�6C   $	��Top=�6o   $	��671��6�   . 5      %  System.Windows.Forms.PictureBox  -
   5        pictureBox1��   SizeMode$ StretchImage=�5   >   $	 150��6�   5        5   
   -   5        $��windowsFormsHost6��5   V   $��42��6   $
��Left=�6'   $��
10,275,0,0q�6B   $	��Top=�6o   $	��110��6�   $ 0.322,0.867&�6�   . 5         System.Windows.Forms.Label     Text$ 文字内容：��6$   $	 150��61   5      5      5       