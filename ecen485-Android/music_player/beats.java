package com.example.uriahnewkirk.funky_beats;

import android.os.Environment;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.widget.AdapterView;
import android.widget.ArrayAdapter;
import android.widget.Button;
import android.widget.ImageButton;
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

//Uriah Newkirk
//Music Player application :)

public class beats extends AppCompatActivity {

    FirebaseDatabase database = FirebaseDatabase.getInstance();
    DatabaseReference myRef= database.getReference("files");

    ListView mList;
    SeekBar playing;
    MenuItem settings, contact;
    boolean playing_s = false;
    ImageButton ppause, p_song, n_song;
    int current;

    ArrayList<String> aList = new ArrayList<>();

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_beats);
        //myRef.setValue("Does this work?");

        ppause = (ImageButton) findViewById(R.id.play_pause);
        p_song  = (ImageButton) findViewById(R.id.rewind);
        n_song = (ImageButton) findViewById(R.id.forward);

        File music = new File(Environment.getExternalStorageDirectory().getAbsolutePath() + "/Music/");
        System.out.println(music.getAbsolutePath().toString());

        File f = new File(music.getAbsolutePath());

        addFiles(f);


        ArrayAdapter<String> adpt = new ArrayAdapter<>(this, android.R.layout.simple_list_item_1, aList);

        mList = (ListView) findViewById(R.id.list_the);

        mList.setAdapter(adpt);


        mList.setOnItemClickListener(new AdapterView.OnItemClickListener() {
            @Override
            public void onItemClick(AdapterView<?> parent, View view, int position, long id) {

                Toast.makeText(getApplicationContext(), "Now Playing: " + aList.get(position), Toast.LENGTH_LONG).show();
                current = position;
                ppause.setImageResource(android.R.drawable.ic_media_pause);
                playing_s =true;
                //Intent j = new Intent(getApplicationContext(), beats_song.class);
                //startActivity(j);


            }
        });
    }


    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        //inflate menu
        getMenuInflater().inflate(R.menu.menu_the, menu);
        return true;
    }


    public void addFiles(File x) {
        File[] files = x.listFiles();
        for (File oneFile : files) {
            if(oneFile.isDirectory()) {
                addFiles(oneFile);
            } else {
                if(oneFile.getName().endsWith(".mp3"))
                aList.add(oneFile.getName());
            }
        }
    }

/*    public void writeToDatabase(ArrayList<String> songs){
        for(int i=0; i<songs.size(); i++){
            String file=songs.get(i).replace(".mp3", "");
            if(!(songs.get(i).contains("/") || songs.get(i).contains("."))){
                myRef.child("files/"+file).setValue(file);
            }
        }
    }*/

    public void onClick(View view) {
        if (view.getId() == R.id.play_pause) {
            playing_s = !playing_s;
            if (playing_s)
                ppause.setImageResource(android.R.drawable.ic_media_pause);
            else
                ppause.setImageResource(android.R.drawable.ic_media_play);

        }
        if (view.getId() == R.id.rewind) {
            current -= 1;
            Toast.makeText(getApplicationContext(), "Now Playing: " + aList.get(current), Toast.LENGTH_LONG).show();
            ppause.setImageResource(android.R.drawable.ic_media_pause);
            playing_s =true;
        }
        if (view.getId() == R.id.forward) {
            current += 1;
            Toast.makeText(getApplicationContext(), "Now Playing: " + aList.get(current), Toast.LENGTH_LONG).show();
            ppause.setImageResource(android.R.drawable.ic_media_pause);
            playing_s =true;
        }
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
                    Intent c = new Intent(getApplicationContext(), beats_contact.class);
                    startActivity(c);
                    item.setChecked(false);
                }
                return true;
            default:
                return super.onOptionsItemSelected(item);
        }
    }
}


