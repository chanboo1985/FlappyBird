/****************************************************************************
Copyright (c) 2008-2010 Ricardo Quesada
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (c) 2011      Zynga Inc.
Copyright (c) 2013-2014 Chukong Technologies Inc.
 
http://www.cocos2d-x.org

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
****************************************************************************/
package org.cocos2dx.cpp;

import org.cocos2dx.lib.Cocos2dxActivity;

import com.umeng.socialize.bean.RequestType;
import com.umeng.socialize.controller.UMServiceFactory;
import com.umeng.socialize.controller.UMSocialService;
import com.umeng.socialize.sso.SinaSsoHandler;
import com.umeng.socialize.sso.TencentWBSsoHandler;

import android.app.Activity;
import android.os.Bundle;
import android.os.Handler;
import android.os.Looper;

public class AppActivity extends Cocos2dxActivity {
	
	/** 
     * Handler, 用于包装友盟的openShare方法，保证openShare方法在UI线程执行 
     */  
    private static Handler mHandler = null;  
    /** 
     * 保存当前Activity实例， 静态变量 
     */  
    private static Activity mActivity = null;  
    /** 
     * 友盟Social SDK实例，整个SDK的Controller 
     */  
    private static UMSocialService mController = UMServiceFactory.getUMSocialService(  
                    "com.umeng.cocos2dx", RequestType.SOCIAL);  
  
    /** 
     * onCreate方法 
     */  
    protected void onCreate(Bundle savedInstanceState) {  
        super.onCreate(savedInstanceState);  
        mActivity = this;  
    }
    
    /** 
     * @Title:  openShareBoard 
     * @Description:  
     *       调用友盟的openShare方法， 打开分享平台选择面板 
     * @throws 
     */  
    public static void openShareBoard() {  
        mHandler = new Handler(Looper.getMainLooper());  
        mHandler.postDelayed(new Runnable() {  
  
            @Override  
            public void run() {  
                if (mActivity != null) {  
                    /** 
                     *   设置新浪微博、QQ空间、腾讯微博的Handler,进行SSO授权 
                     *    
                     *   注意 ： 新浪平台支持SSO则需要把友盟提供的com.sina.sso拷进src里面， 
                     *      需要将友盟提供的libs、res文件拷贝到您的工程对应的目录里面.  
                     */  
                    mController.getConfig().setSsoHandler(new SinaSsoHandler());
//                    mController.getConfig().setSsoHandler(new QZoneSsoHandler(activity, appId, appKey));
                    mController.getConfig().setSsoHandler(new TencentWBSsoHandler());  
                      
                    // 打开友盟的分享平台选择面板  
                    mController.openShare(mActivity, false);  
                }  
            }  
        }, 100);  
    }  
}
