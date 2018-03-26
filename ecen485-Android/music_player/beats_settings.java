package com.example.uriahnewkirk.funky_beats;


import android.os.Environment;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.ContextMenu;
import android.view.Menu;
import android.view.MenuInflater;
import android.view.MenuItem;
import android.view.View;
import android.view.ContextMenu;
import android.view.ContextMenu.ContextMenuInfo;
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
import java.io.File;
import android.media.MediaMetadataRetriever;

import com.google.firebase.database.DatabaseReference;
import com.google.firebase.database.FirebaseDatabase;


public class beats_settings extends AppCompatActivity {

    private static final int EDIT_ID = Menu.FIRST+2;
    Button theme_b;
    String themeN;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        Utils.onActivityCreateSetTheme(this);
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_settings);


        theme_b = (Button) findViewById(R.id.theme_button);
        registerForContextMenu(theme_b);

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


    public void onClick(View v) {
        if (v.getId() == R.id.theme_button) {
            v.showContextMenu();
        }
    }


    @Override
    public void onCreateContextMenu(ContextMenu menu, View v, ContextMenuInfo menuI) {
        MenuInflater infl = getMenuInflater();
        infl.inflate(R.menu.contx_2, menu);

    }

    @Override
    public boolean onContextItemSelected(MenuItem mItem) {
        if (mItem.getItemId() == R.id.default_the) {
            Utils.changeTheme(this, Utils.THEME_DEFAULT1);
            return true;

        } else if (mItem.getItemId() == R.id.blue_the) {
            Utils.changeTheme(this, Utils.THEME_BLUE);
            return true;

        } else if (mItem.getItemId() == R.id.green_the) {
            Utils.changeTheme(this, Utils.THEME_GREEN);
            return true;

//        } else if (mItem.getItemId() == R.id.black) {
//            Utils.changeTheme(this, Utils.THEME_BLACK);
//            return true;

        }
        else
            return onContextItemSelected(mItem);
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
                    item.setChecked(false);
                }
                return true;
            case R.id.menu2:
                if (item.isChecked()) {
                    item.setChecked(false);
                } else {
                    item.setChecked(true);
                    Intent c = new Intent(getApplicationContext(), beats_contact.class);
                    startActivity(c);
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