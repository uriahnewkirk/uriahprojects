package com.example.uriahnewkirk.funky_beats;

import android.*;
import android.Manifest;
import android.app.Activity;
import android.content.SharedPreferences;
import android.content.pm.PackageManager;
import android.media.MediaPlayer;
import android.os.Environment;
import android.os.Handler;
import android.os.Message;
import android.os.SystemClock;
import android.preference.PreferenceManager;
import android.support.v4.app.ActivityCompat;
import android.support.v4.content.ContextCompat;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;
import android.view.ContextMenu;
import android.view.Menu;
import android.view.MenuInflater;
import android.view.MenuItem;
import android.view.View;
import android.view.ContextMenu;
import android.view.ContextMenu.ContextMenuInfo;
import android.view.ViewGroup;
import android.widget.AdapterView;
import android.widget.ArrayAdapter;
import android.widget.Button;
import android.widget.ImageButton;
import android.widget.RelativeLayout;
import android.view.ContextMenu;
import android.view.ContextMenu.ContextMenuInfo;
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

    private static final int EDIT_ID = Menu.FIRST+2;


    MediaPlayer mPlay = new MediaPlayer();

    ArrayAdapter<Song> adpt;
    TextView dEnd, dStart, dPath, displayName, nowP;
    ListView mList;
    SeekBar sProgress;
    MenuItem settings, contact;
    boolean playing_s = false;
    boolean stop; //timer
    long song_d, h, m, s, updateT, cTime, duration, song_id;
    long millis;
    String extract, s_info;
    String song_o, timeString;
    ImageButton ppause, p_song, n_song;
    int c_s, c_ss, c_m, c_h, current, maxV, currentV, d_song, barP, position_the;
    final private int userPermissions=6;

    ArrayList<Song> aList = new ArrayList<>();
    ArrayList<String> pList = new ArrayList<>();




    Handler handleB = new Handler();


    protected void onCreate(Bundle savedInstanceState) {
//        checkforPermissions();
        ActivityCompat.requestPermissions(beats.this, new String[]{Manifest.permission.READ_EXTERNAL_STORAGE}, 1);
        Utils.onActivityCreateSetTheme(this);
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_beats);




       // if(checkSelfPermission(Manifest.permission.READ_EXTERNAL_STORAGE) != PackageManager.PERMISSION_GRANTED) {

      //  }

        //Utils.onActivityCreateSetTheme(this);

        //myRef.setValue("Does this work?");
        //addControls();
        //addEvents();

        dStart = (TextView)findViewById(R.id.tView1);
        dEnd = (TextView) findViewById(R.id.tView);
        displayName = (TextView) findViewById(R.id.username);
        nowP = (TextView) findViewById(R.id.nowP);
        //dPath = (TextView)findViewById(R.id.path_v);

        sProgress = (SeekBar)findViewById(R.id.sBar1);

        sProgress.setProgress(barP);
        //set value for full progress bar

        ppause = (ImageButton) findViewById(R.id.play_pause);
        p_song  = (ImageButton) findViewById(R.id.rewind);
        n_song = (ImageButton) findViewById(R.id.forward);

        if(ContextCompat.checkSelfPermission(this, Manifest.permission.WRITE_EXTERNAL_STORAGE) == PackageManager.PERMISSION_GRANTED) {
            File music = new File(Environment.getExternalStorageDirectory().getAbsolutePath() + "/Music/");
            File f = new File(music.getAbsolutePath());
            addFiles(f);
        } else {
            Toast.makeText(getApplicationContext(), "Enable permissions and restart app to load songs", Toast.LENGTH_LONG).show();
        }



        adpt = new ArrayAdapter<>(this, android.R.layout.simple_list_item_1, aList);

        mList = (ListView) findViewById(R.id.list_the);

        mList.setAdapter(adpt);
        registerForContextMenu(mList);

/*        mList.setOnItemLongClickListener(new AdapterView.OnItemLongClickListener() {
            @Override
            public boolean onItemLongClick(AdapterView<?> arg0, View arg1, int position, long id) {
                position_the = position;
                return true;
            }
        });*/

        mList.setOnItemClickListener(new AdapterView.OnItemClickListener() {
            @Override
            public void onItemClick(AdapterView<?> parent, View view, int position, long id) {

                mPlay.stop();
                mPlay.reset();
                //find a way to reset the player when a new song is selected??
                Toast.makeText(getApplicationContext(), "Now Playing: " + aList.get(position).getName(), Toast.LENGTH_LONG).show();
                current = position;

                ppause.setImageResource(android.R.drawable.ic_media_pause);
                playing_s = true;

                try {
                    mPlay.setDataSource(aList.get(position).getPath());
                    mPlay.prepare();

                } catch(Exception e) {
                    //file not found/out of bounds
                }
                view.setSelected(true);
//                adpt.notifyDataSetChanged();
                song_d = mPlay.getDuration() / 1000;
                mPlay.start();

                handleB.postDelayed(run_time,0);
                //start thread immediately

                Thread rThread = new Thread (run_time);
                rThread.start();

                Thread proThread = new Thread (run_progress);
                proThread.start();


                song_d = findDuration(song_d);
                dEnd.setText(String.format("%02d",m) +":" +String.format("%02d",s));
                nowP.setText("Now Playing: " +aList.get(position).getName());

            }
        });

        sProgress.setOnSeekBarChangeListener(new SeekBar.OnSeekBarChangeListener() {
            @Override
            public void onProgressChanged(SeekBar seekBar, int progress, boolean fromUser) {

                if(fromUser) {
                    System.out.println("Progress " + progress);
//                    seekBar.setProgress(progress);
                    mPlay.seekTo(progress);


                    mPlay.start();

                    handleB.postDelayed(run_progress,0);
                    handleB.postDelayed(run_time,0);
                }
            }

            @Override
            public void onStartTrackingTouch(SeekBar seekBar) {
                mPlay.pause();

                handleB.removeCallbacks(run_time);
                handleB.removeCallbacks(run_progress);
            }

            @Override
            public void onStopTrackingTouch(SeekBar seekBar) {
            }
        });

        MediaPlayer.OnCompletionListener cList = new MediaPlayer.OnCompletionListener() {
            @Override
            public void onCompletion(MediaPlayer mp) {

                if (current == aList.size() - 1) {
                    current = 0;
                } else {
                    current += 1;
                }
                mPlay.reset();
                    try {
                        mPlay.setDataSource(aList.get(current).getPath());
                        mPlay.prepare();
                    } catch (Exception e) {

                    }
                mPlay.start();

                song_d = findDuration(song_d);
                dEnd.setText(String.format("%02d",m) +":" +String.format("%02d",s));
                nowP.setText("Now Playing: " +aList.get(current).getName());
            }
        };
        mPlay.setOnCompletionListener(cList);
    }

    private void checkforPermissions() {
        if(ContextCompat.checkSelfPermission(this, Manifest.permission.WRITE_EXTERNAL_STORAGE) != PackageManager.PERMISSION_GRANTED &&
                ContextCompat.checkSelfPermission(this, Manifest.permission.WRITE_EXTERNAL_STORAGE) != PackageManager.PERMISSION_GRANTED) {

            ActivityCompat.requestPermissions(this, new String[]{ Manifest.permission.WRITE_EXTERNAL_STORAGE}, userPermissions);
        } else {

        }
    }

    @Override
    public void onRequestPermissionsResult(int requestCode, String[] permissions, int[] grantResults) {


        switch (requestCode) {
            case userPermissions:
                if (grantResults[0] == PackageManager.PERMISSION_GRANTED) {
                    // Permission Granted
//                    File music = new File(Environment.getExternalStorageDirectory().getAbsolutePath() + "/Music/");
//                    File f = new File(music.getAbsolutePath());
//                    addFiles(f);
//                    adpt = new ArrayAdapter<>(this, android.R.layout.simple_list_item_1, aList);
//                    adpt.notifyDataSetChanged();
                    super.onCreate(new Bundle());
//                    insertDummyContact();
                } else {
                    // Permission Denied
                    Toast.makeText(this, "Storage Permissions Denied", Toast.LENGTH_SHORT).show();
                }
                break;
            default:
                super.onRequestPermissionsResult(requestCode, permissions, grantResults);
        }


    }



//        if (requestCode == userPermissions) {
//            if (grantResults.length > 0 && grantResults[0] == PackageManager.PERMISSION_GRANTED) {
////                initializeFragments();
//            } else {
//
//            }
//        }
//        super.onRequestPermissionsResult(requestCode, permissions, grantResults);
//    }
        //        // Here, thisActivity is the current activity
//        if (ContextCompat.checkSelfPermission(this,
//                Manifest.permission.READ_EXTERNAL_STORAGE) != PackageManager.PERMISSION_GRANTED) {
//
//            // Permission is not granted
//            // Should we show an explanation?
//            if (ActivityCompat.shouldShowRequestPermissionRationale(this, Manifest.permission.READ_EXTERNAL_STORAGE)) {
//
//                // Show an explanation to the user *asynchronously* -- don't block
//                // this thread waiting for the user's response! After the user
//                // sees the explanation, try again to request the permission.
//
//            } else {
//
//                // No explanation needed; request the permission
//                ActivityCompat.requestPermissions(this,
//                        new String[]{Manifest.permission.READ_CONTACTS},
//                        userPermissions);
//
//                // MY_PERMISSIONS_REQUEST_READ_CONTACTS is an
//                // app-defined int constant. The callback method gets the
//                // result of the request.
//            }
//        } else {
//            // Permission has already been granted
//        }




    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        //inflate menu
        menu.add(Menu.NONE, EDIT_ID, Menu.NONE, "Preferences")
                .setIcon(R.drawable.ic_launcher_background)
                .setAlphabeticShortcut('e');
        getMenuInflater().inflate(R.menu.menu_the, menu);


        return(super.onCreateOptionsMenu(menu));
    }



    @Override
    public void onCreateContextMenu(ContextMenu menu, View v, ContextMenuInfo menuI) {
        AdapterView.AdapterContextMenuInfo info = (AdapterView.AdapterContextMenuInfo) menuI;
        song_o = ((TextView)info.targetView).getText().toString();
        song_id = info.id;

        super.onCreateContextMenu(menu, v, menuI);
        MenuInflater infl = getMenuInflater();
        infl.inflate(R.menu.contx_1, menu);
    }





    @Override
    public boolean onContextItemSelected(MenuItem item) {
        if(item.getItemId() == R.id.fave) {

            if(aList.get(current).getFavorite()) {
                aList.get(current).removeFavorite();
                Toast.makeText(this, "Removed from favorites", Toast.LENGTH_SHORT).show();
            }
            else {
                aList.get(current).addFavorite();
                Toast.makeText(this, "Added to favorites", Toast.LENGTH_SHORT).show();
            }
        }

        else if(item.getItemId() == R.id.delete) {
            adpt.remove(aList.get((int)song_id));
//            mPlay.stop();
//            mPlay.reset();
            //what if user deletes the current song, what errors could occur??
            Toast.makeText(this, "song deleted", Toast.LENGTH_SHORT).show();
            adpt.notifyDataSetChanged();

        }
        else
            return false;
        return true;
/*
        AdapterView.AdapterContextMenuInfo info = (AdapterView.AdapterContextMenuInfo)item.getMenuInfo();
        int menuItemIndex = item.getItemId();
        String[] song_o = {"Edit", "Delete"};
        String menuItemName = song_o[menuItemIndex];
        String listItemName = aList.get(info.position).getName();


        if(menuItemName.equals("Delete")) {
            aList.remove(current);
        }
        else if(menuItemName.equals("Favorite")) {
            if(aList.get(current).getFavorite()) {
                aList.get(current).removeFavorite();
            }
            else {
                aList.get(current).addFavorite();
            }
        }
        return true;
        */

    }



    public void addFiles(File x) {
        File[] files = x.listFiles();
        for (File oneFile : files) {
            if(oneFile.isDirectory()) {
                addFiles(oneFile);
            } else {
                if(oneFile.getName().endsWith(".mp3")) {
                    Song s = new Song(oneFile.getName(), oneFile.getAbsolutePath());
                    aList.add(s);
                }
            }
        }
    }


    public Runnable run_time = new Runnable() {
        @Override
        public void run() {

            millis = mPlay.getCurrentPosition();
            long secs = millis / 1000 % 60;
            long mins = millis / 1000 /60 % 60;
            long hours = millis / 1000 / 60 / 60;


            timeString = String.format("%02d:%02d", mins, secs);

            runOnUiThread(new Runnable() {
                @Override
                public void run() {

                    dStart.setText(timeString);

//                    if(sProgress != null) {
//                        sProgress.setMax(0);
//                        sProgress.setMax(100);
//                        barP = (int)((long)(c_ss) / duration *100.00);
//                        tv2.setText(barP);
//                        sProgress.setProgress(barP);
//                    }
                }
            });
            //sProgress.setProgress((int)((long)c_ss / duration));
            //sProgress.setProgress((int)((long)(mPlay.getCurrentPosition() / 1000) / duration));
            handleB.postDelayed(this, 100);
        }
    };


    public Runnable run_progress = new Runnable() {

        @Override
        public void run() {

            if(mPlay.isPlaying()) {
                int mediaPos = mPlay.getCurrentPosition();
                int mediaNew = mPlay.getDuration();
                sProgress.setMax(mediaNew);
                sProgress.setProgress(mediaPos);

                handleB.postDelayed(this, 100);
            }

        }
    };

    public void onClick(View view) {
        if (view.getId() == R.id.play_pause) {
            //playing_s = !playing_s;
            if (mPlay.isPlaying()) {
                ppause.setImageResource(android.R.drawable.ic_media_play);
                mPlay.pause();
                handleB.removeCallbacks(run_time);
                handleB.removeCallbacks(run_progress);

            } else {
                ppause.setImageResource(android.R.drawable.ic_media_pause);

                try {
                    handleB.postDelayed(run_progress, 0);
                    handleB.postDelayed(run_time, 0);
                    mPlay.start();
                } catch (Exception e) {

                }

            }
        }
        if (view.getId() == R.id.rewind) {
            if (current != 0) {
                current -= 1;
            } else {
                current = aList.size() - 1;
            }
                mPlay.reset();
                Toast.makeText(getApplicationContext(), "Now Playing: " + aList.get(current).getName(), Toast.LENGTH_LONG).show();
                ppause.setImageResource(android.R.drawable.ic_media_pause);
                try {
                    mPlay.setDataSource(aList.get(current).getPath());
                    mPlay.prepare();
                    mPlay.start();
                } catch (Exception e) {

                }
                song_d = mPlay.getDuration() / 1000;
                song_d = findDuration(song_d);
                dEnd.setText(String.format("%02d", m) + ":" + String.format("%02d", s));
                nowP.setText("Now Playing: " +aList.get(current).getName());

    }
        if (view.getId() == R.id.forward) {

            if(current != (aList.size() - 1)) {
                current += 1;
            } else {
                current = 0;
            }
            mPlay.reset();
            Toast.makeText(getApplicationContext(), "Now Playing: " + aList.get(current).getName(), Toast.LENGTH_LONG).show();
            ppause.setImageResource(android.R.drawable.ic_media_pause);
            try {
                mPlay.setDataSource(aList.get(current).getPath());
                mPlay.prepare();
                mPlay.start();
            } catch(Exception e) {

            }
            song_d = mPlay.getDuration() / 1000;

            song_d = findDuration(song_d);
            dEnd.setText(String.format("%02d",m) +":" +String.format("%02d",s));
            nowP.setText("Now Playing: " +aList.get(current).getName());
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
            case EDIT_ID:
                startActivity(new Intent(this, EditPreferences.class));
                return(true);
            default:
                return super.onOptionsItemSelected(item);
        }
    }

    @Override
    public void onResume() {
        super.onResume();

        SharedPreferences prefs = PreferenceManager.getDefaultSharedPreferences(this);

        if(prefs.getBoolean("welcome", true)) {
            displayName.setText("Hello " + prefs.getString("uName", "user") + " how may I serve you today?");
        }
        else {
            displayName.setText("");
        }

    }


    //@Override
    public void onRequestPermissionResult(int requestCode, String permissions[], int[] grantResults) {
        switch (requestCode) {
            case 1: {
                if (grantResults.length > 0 && grantResults[0] == PackageManager.PERMISSION_GRANTED) {
                }
                else {
                    Toast.makeText(getApplicationContext(), "You must enable permissions on your device in order for the List to show ", Toast.LENGTH_LONG).show();
                }
                }
            }
        }

    public long findDuration(long t) {
//calculate max duration of song in hours, minutes, & seconds
        h = t / 3600;
        m = (t - h * 3600) / 60;
        s =  t - (h*3600 + m * 60);
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
