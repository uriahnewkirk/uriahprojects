package com.example.uriahnewkirk.funky_beats;

import android.media.MediaPlayer;
import android.os.Environment;
import android.os.Handler;
import android.os.Message;
import android.os.SystemClock;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;
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

import org.w3c.dom.Text;

//Uriah Newkirk
//Music Player application :)

public class beats extends AppCompatActivity {

    FirebaseDatabase database = FirebaseDatabase.getInstance();
    DatabaseReference myRef= database.getReference("files");

    MediaMetadataRetriever mData = new MediaMetadataRetriever();

    MediaPlayer mPlay = new MediaPlayer();

    TextView dEnd, dStart, dPath;
    ListView mList;
    SeekBar sProgress;
    MenuItem settings, contact;
    boolean playing_s = false;
    long song_d, h, m, s, startTime, tBuffer, updateT, cTime, duration;
    String extract;
    ImageButton ppause, p_song, n_song;
    int c_s, c_ss, c_m, c_h, current, maxV, currentV, d_song, barP;

    ArrayList<String> aList = new ArrayList<>();
    ArrayList<String> pList = new ArrayList<>();


    Handler handleB = new Handler();


    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_beats);
        //myRef.setValue("Does this work?");

        dStart = (TextView)findViewById(R.id.tView1);
        dEnd = (TextView) findViewById(R.id.tView);
        dPath = (TextView)findViewById(R.id.path_v);

        sProgress = (SeekBar)findViewById(R.id.sBar1);

        sProgress.setProgress(barP);
        //set value for full progress bar

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

                mPlay.stop();
                mPlay.reset();
                //find a way to reset the player when a new song is selected??
                Toast.makeText(getApplicationContext(), "Now Playing: " + aList.get(position), Toast.LENGTH_LONG).show();
                current = position;
                dPath.setText("path:" +pList.get(position));
                ppause.setImageResource(android.R.drawable.ic_media_pause);
                playing_s = true;
                mData.setDataSource(pList.get(position));

                try {
                    mPlay.setDataSource(pList.get(position));
                    mPlay.prepare();
                    //d_song = mPlay.getDuration();
                    song_d = Long.parseLong(mData.extractMetadata(MediaMetadataRetriever.METADATA_KEY_DURATION));
                    //song length in milliseconds

                } catch(Exception e) {
                    //file not found/out of bounds
                }
                mPlay.start();

                handleB.postDelayed(run_it,0);
                //start thread immediately

                Thread rThread = new Thread (run_it);
                rThread.start();
                startTime = SystemClock.uptimeMillis();

                song_d = findDuration(song_d);
                dEnd.setText(String.format("%02d",m) +":" +String.format("%02d",s));
            }
        });

        sProgress.setOnSeekBarChangeListener(new SeekBar.OnSeekBarChangeListener() {
            @Override
            public void onProgressChanged(SeekBar seekBar, int progress, boolean fromUser) {

            }

            @Override
            public void onStartTrackingTouch(SeekBar seekBar) {

            }

            @Override
            public void onStopTrackingTouch(SeekBar seekBar) {

            }
        });

        MediaPlayer.OnCompletionListener cList = new MediaPlayer.OnCompletionListener() {
            @Override
            public void onCompletion(MediaPlayer mp) {
                //current += 1;
                mPlay.reset();
                if(pList.get(current) != null) {
                    try {
                        mPlay.setDataSource(pList.get(current));
                        mPlay.prepare();
                    } catch (Exception e) {

                    }
                }
                else {
                    current = 0;
                    try {
                        mPlay.setDataSource(pList.get(0));
                        mPlay.prepare();
                    } catch (Exception e) {

                    }
                }
                mPlay.start();

                startTime = SystemClock.uptimeMillis();

                song_d = findDuration(song_d);
                dEnd.setText(String.format("%02d",m) +":" +String.format("%02d",s));
            }
        };
        mPlay.setOnCompletionListener(cList);
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
                if(oneFile.getName().endsWith(".mp3")) {
                    aList.add(oneFile.getName());
                    pList.add(oneFile.getAbsolutePath());
                }
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

    public Runnable run_it = new Runnable() {
        @Override
        public void run() {
            cTime = SystemClock.uptimeMillis() - startTime;
            updateT = tBuffer + cTime;
            c_ss = (int) (updateT / 1000);
            c_m = c_ss / 60;
            c_s = c_ss % 60;
            cTime = (int) (updateT % 1000);

            runOnUiThread(new Runnable() {
                @Override
                public void run() {
                    dStart.setText(String.format("%02d", c_m) +":" +String.format("%02d", c_s));

                    if(sProgress != null) {
                        //sProgress.setMax(0);
                        //sProgress.setMax(100);
                        //barP = (int)((long)(c_ss) / duration *100.00);
                        //tv2.setText(barP);
                        //sProgress.setProgress(barP);
                    }
                }
            });
            //sProgress.setProgress((int)((long)c_ss / duration));
            //sProgress.setProgress((int)((long)(mPlay.getCurrentPosition() / 1000) / duration));
            handleB.postDelayed(this, 0);
        }
    };

    public void onClick(View view) {
        if (view.getId() == R.id.play_pause) {
            //playing_s = !playing_s;
            if (mPlay.isPlaying()) {
                ppause.setImageResource(android.R.drawable.ic_media_play);
                mPlay.pause();
                handleB.removeCallbacks(run_it);
                tBuffer += cTime;
            }
            else {
                ppause.setImageResource(android.R.drawable.ic_media_pause);
                try {
                    handleB.postDelayed(run_it,0);
                    mPlay.start();
                } catch(Exception e) {

                }
            }
        }
        if (view.getId() == R.id.rewind) {
            mPlay.reset();
            current -= 1;
            Toast.makeText(getApplicationContext(), "Now Playing: " + aList.get(current), Toast.LENGTH_LONG).show();
            ppause.setImageResource(android.R.drawable.ic_media_pause);
            mData.setDataSource(pList.get(current));
            try {
                mPlay.setDataSource(pList.get(current));
                mPlay.prepare();
                mPlay.start();
            } catch(Exception e) {

            }
            song_d = Long.parseLong(mData.extractMetadata(MediaMetadataRetriever.METADATA_KEY_DURATION));

            startTime = SystemClock.uptimeMillis();

            song_d = findDuration(song_d);
            dEnd.setText(String.format("%02d",m) +":" +String.format("%02d",s));
        }
        if (view.getId() == R.id.forward) {
            mPlay.reset();
            current += 1;
            Toast.makeText(getApplicationContext(), "Now Playing: " + aList.get(current), Toast.LENGTH_LONG).show();
            ppause.setImageResource(android.R.drawable.ic_media_pause);
            mData.setDataSource(pList.get(current));
            try {
                mPlay.setDataSource(pList.get(current));
                mPlay.prepare();
                mPlay.start();
            } catch(Exception e) {

            }
            song_d = Long.parseLong(mData.extractMetadata(MediaMetadataRetriever.METADATA_KEY_DURATION));

            startTime = SystemClock.uptimeMillis();

            song_d = findDuration(song_d);
            dEnd.setText(String.format("%02d",m) +":" +String.format("%02d",s));
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

    public long findDuration(long j) {
//calculate max duration of song in hours, minutes, & seconds
        duration = j / 1000;
        h = duration / 3600;
        m = (duration - h * 3600) / 60;
        s = duration - (h * 3600 + m * 60);
        //String durationV;
       /* if (h == 0) {
            durationValue = String.format(
                    activity.getString(R.string.details_ms), m, s);
        } else {
            durationValue = String.format(
                    activity.getString(R.string.details_hms), h, m, s);
        }*/
       return duration;
    }
}
