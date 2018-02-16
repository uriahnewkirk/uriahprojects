package com.example.uriahnewkirk.funky_beats;


import android.net.Uri;
import android.os.Environment;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
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

    TextView info;
    Button go;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_contact);

        info = (TextView)findViewById(R.id.information);
        go = (Button) findViewById(R.id.github);
    }

    public void onClick(View view) {
        if(view.getId()==R.id.github) {
            Intent o = new Intent();
            o.setAction(Intent.ACTION_VIEW);
            o.addCategory(Intent.CATEGORY_BROWSABLE);
            o.setData(Uri.parse("https://github.com/uriahnewkirk/uriahprojects"));
            startActivity(o);
        }
    }


    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        //inflate menu
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
            default:
                return super.onOptionsItemSelected(item);
        }
    }

}