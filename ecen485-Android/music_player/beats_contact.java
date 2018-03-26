package com.example.uriahnewkirk.funky_beats;


import android.net.Uri;
import android.os.Environment;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.webkit.WebView;
import android.widget.AdapterView;
import android.widget.ArrayAdapter;
import android.widget.Button;
import android.widget.RelativeLayout;
import android.widget.TextView;
import android.widget.ListView;
import android.widget.SeekBar;
import android.content.Intent;
import android.widget.Toast;
import java.util.ArrayList;
import java.lang.String;
import java.io.File;
import android.media.MediaMetadataRetriever;

import com.google.firebase.database.DatabaseReference;
import com.google.firebase.database.FirebaseDatabase;


public class beats_contact extends AppCompatActivity {

    private static final int EDIT_ID = Menu.FIRST+2;
    TextView info;
    Button go;


    @Override
    protected void onCreate(Bundle savedInstanceState) {
        Utils.onActivityCreateSetTheme(this);
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_contact);

        info = (TextView)findViewById(R.id.information);
        go = (Button) findViewById(R.id.github);
    }

    public void onClick(View view) {
        if(view.getId()==R.id.github) {
            Intent o = new Intent(getApplicationContext(), githubWeb.class);
            startActivity(o);
        }
    }


    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        //inflate menu
        menu.add(Menu.NONE, EDIT_ID, Menu.NONE, "Preferences")
                .setIcon(R.drawable.ic_launcher_background)
                .setAlphabeticShortcut('e');
        getMenuInflater().inflate(R.menu.menu_the, menu);
        return true;
    }


    @Override
    public boolean onOptionsItemSelected(MenuItem item) {
        RelativeLayout mLayout = (RelativeLayout)findViewById(R.id.trucks);

        switch(item.getItemId()) {
            case R.id.menu1:
                if (item.isChecked()) {
                    item.setChecked(false);
                } else {
                    item.setChecked(true);
                    Intent x = new Intent(getApplicationContext(), beats_settings.class);
                    startActivity(x);
                    item.setChecked(false);
                }
                return true;
            case R.id.menu2:
                if (item.isChecked()) {
                    item.setChecked(false);
                } else {
                    item.setChecked(true);
                    item.setChecked(false);
                }
                return true;
            case EDIT_ID:
                startActivity(new Intent(this, EditPreferences.class));
                return(true);
            default:
                return super.onOptionsItemSelected(item);
        }
    }

}