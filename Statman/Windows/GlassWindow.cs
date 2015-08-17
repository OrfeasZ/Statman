// -------------------------------------------------------------------------------
// 
// This file is part of the FluidKit project: http://www.codeplex.com/fluidkit
// 
// Copyright (c) 2008, The FluidKit community 
// All rights reserved.
// 
// Redistribution and use in source and binary forms, with or without modification, 
// are permitted provided that the following conditions are met:
// 
// * Redistributions of source code must retain the above copyright notice, this 
// list of conditions and the following disclaimer.
// 
// * Redistributions in binary form must reproduce the above copyright notice, this 
// list of conditions and the following disclaimer in the documentation and/or 
// other materials provided with the distribution.
// 
// * Neither the name of FluidKit nor the names of its contributors may be used to 
// endorse or promote products derived from this software without specific prior 
// written permission.
// 
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND 
// ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED 
// WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE 
// DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR 
// ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES 
// (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; 
// LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON 
// ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT 
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS 
// SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE. 
// -------------------------------------------------------------------------------

using System;
using System.Runtime.InteropServices;
using System.Windows;
using System.Windows.Input;
using System.Windows.Interop;
using System.Windows.Shapes;

namespace Statman.Windows
{
    [TemplatePart(Name = "PART_TitleBar", Type = typeof(Rectangle))]
    public class GlassWindow : Window
    {
        private WindowInteropHelper m_InteropHelper;

        static GlassWindow()
        {
            DefaultStyleKeyProperty.OverrideMetadata(typeof(GlassWindow), new FrameworkPropertyMetadata(typeof(GlassWindow)));
        }

        public override void OnApplyTemplate()
        {
            base.OnApplyTemplate();

            m_InteropHelper = new WindowInteropHelper(this);
            AttachToVisualTree();
        }

        private void AttachToVisualTree()
        {
            // Title Bar
            var s_TitleBar = GetChildControl<Rectangle>("PART_TitleBar");

            if (s_TitleBar != null)
                s_TitleBar.MouseLeftButtonDown += OnTitleBarMouseDown;
        }

        private void OnTitleBarMouseDown(object p_Sender, MouseButtonEventArgs p_Args)
        {
            if (ResizeMode != ResizeMode.NoResize && p_Args.ClickCount == 2)
            {
                // 
                return;
            }

            DragMove();
        }

        protected T GetChildControl<T>(string p_CtrlName) 
            where T : DependencyObject
        {
            var s_Control = GetTemplateChild(p_CtrlName) as T;
            return s_Control;
        }

        protected void MoveWindow(Rect p_Rect)
        {
            MoveWindow(m_InteropHelper.Handle, (int)p_Rect.Left, (int)p_Rect.Top, (int)p_Rect.Width, (int)p_Rect.Height, false);
        }

      
        #region P/Invoke and Helper Method

        [DllImport("user32")]
        private static extern Boolean MoveWindow(
            IntPtr hWnd,
            Int32 x, Int32 y,
            Int32 nWidth, Int32 nHeight, Boolean bRepaint);

        #endregion
    }
}