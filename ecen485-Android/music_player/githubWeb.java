package com.example.uriahnewkirk.funky_beats;

import android.support.v7.app.AppCompatActivity;
import android.app.Activity;
import android.os.Bundle;
import android.webkit.WebView;
import android.webkit.WebViewClient;


public class githubWeb extends AppCompatActivity {


    private WebView webView;

    public void onCreate(Bundle savedInstanceState) {
        Utils.onActivityCreateSetTheme(this);
        super.onCreate(savedInstanceState);
        setContentView(R.layout.webview_github);

        webView = (WebView) findViewById(R.id.webView1);
        webView.setWebViewClient(new WebViewClient());
        webView.getSettings().setJavaScriptEnabled(true);
        webView.setVerticalScrollBarEnabled(false);
        webView.setHorizontalScrollBarEnabled(false);
        webView.loadUrl("https://github.com/uriahnewkirk/uriahprojects/blob/master/ecen485-Android/music_player/beats.java");

    }


    @Override
    public void onBackPressed() {

        if(webView.canGoBack()) {
            webView.goBack();
            return;
        }

        super.onBackPressed();
    }

}