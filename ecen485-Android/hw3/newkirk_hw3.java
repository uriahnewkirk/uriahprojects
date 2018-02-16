package com.example.uriahnewkirk.newkirk_hw3;

import android.graphics.Typeface;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.CheckBox;
import android.widget.EditText;
import android.widget.RadioButton;
import android.widget.RadioGroup;
import android.widget.TextView;
import android.graphics.Color;

//Uriah Newkirk
//9 February 2018
//ECEN 485 Android App Development
//Homework #3 part 1

public class newkirk_hw3 extends AppCompatActivity {


    Button bttn1, bttn2;
    RadioButton rbttn_b, rbttn_c, rbttn_s;
    RadioGroup rg_p;
    CheckBox cbox_b, cbox_g;
    TextView tview_p, tview_n, tview_g, tview_done;
    EditText typeName, typeRivalName;

    String gender ="Now tell me, are you a boy or are you a girl?", name="All right. What's your name";
    String pokemon="Now which POKEMON do you want?", begin="Press 'Begin Journey' when you're done.";

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_newkirk_hw3);
        typeName=(EditText)findViewById(R.id.typeName);
        typeRivalName=(EditText)findViewById(R.id.typeRivalName);


        tview_p=(TextView)findViewById(R.id.tview_p);
        tview_n=(TextView)findViewById(R.id.tview_n);
        tview_g=(TextView)findViewById(R.id.tview_g);
        tview_done=(TextView)findViewById(R.id.tview_done);

        cbox_b=(CheckBox)findViewById(R.id.cbox_b);
        cbox_g=(CheckBox)findViewById(R.id.cbox_g);


        bttn1=(Button)findViewById(R.id.bttn1);
        bttn2=(Button)findViewById(R.id.bttn2);

        bttn2.setOnClickListener(new View.OnClickListener()
        {
            public void onClick(View v) {
                if ((cbox_b.isChecked() && !cbox_g.isChecked()) || (!cbox_b.isChecked() && cbox_g.isChecked())) {
                    if (!(typeName.getText().toString().equals(""))) {
                        if (!(typeRivalName.getText().toString().equals(""))) {
                            if (rbttn_b.isChecked() || rbttn_c.isChecked() || rbttn_s.isChecked()) {
                                tview_done.setText(typeName.getText().toString() + "! Your very own POKEMON legend\nis about to unfold! A world of dreams and\nadventures with POKEMON awaits! Let's go!");
                                tview_done.setTextColor(android.graphics.Color.GREEN);
                            }
                            else {
                                tview_done.setText("You need your own POKEMON for your protection.\nPlease choose one.");
                                tview_done.setTextColor(android.graphics.Color.RED);
                            }
                        }
                        else {
                            tview_done.setText("But what about my grandson! What's his name?");
                            tview_done.setTextColor(android.graphics.Color.RED);
                        }
                    }
                    else {
                        tview_done.setText("But what is your name?");
                        tview_done.setTextColor(android.graphics.Color.RED);
                    }
                }
                else {
                    tview_done.setText(gender);
                    tview_done.setTextColor(android.graphics.Color.RED);
                }
            }
        });


        bttn1.setOnClickListener(new View.OnClickListener()
        {
            public void onClick(View v)
            {
/*              rbttn_b.setChecked(false);
                rbttn_c.setChecked(false);
                rbttn_s.setChecked(false);*/

                rg_p.clearCheck();
                cbox_b.setChecked(false);
                cbox_g.setChecked(false);
                tview_g.setText(gender);
                tview_g.setTextColor(android.graphics.Color.GRAY);
                tview_g.setTypeface(Typeface.DEFAULT);
                tview_g.setAllCaps(false);
                tview_p.setText(pokemon);
                tview_p.setTextColor(android.graphics.Color.GRAY);
                tview_done.setText(begin);
                tview_done.setTextColor(android.graphics.Color.GRAY);
                typeName.setText("");
                typeRivalName.setText("");
            }
        });


        rbttn_b=(RadioButton)findViewById(R.id.rbttn_b);
        rbttn_c=(RadioButton)findViewById(R.id.rbttn_c);
        rbttn_s=(RadioButton)findViewById(R.id.rbttn_s);

        rg_p=(RadioGroup)findViewById(R.id.rg_p);

        rg_p.setOnCheckedChangeListener(new RadioGroup.OnCheckedChangeListener() {
            @Override
            public void onCheckedChanged(RadioGroup group, int checkedId) {
                if(rbttn_b.isChecked()/* && !rbttn_c.isChecked() && !rbttn_s.isChecked()*/) {
                    tview_p.setText("Would you like the plant POKEMON Bulbasaur?");
                    tview_p.setTextColor(android.graphics.Color.GREEN);
                }
                if(rbttn_c.isChecked()/* && !rbttn_b.isChecked() && !rbttn_s.isChecked()*/) {
                    tview_p.setText("Would you like the fire POKEMON Charmander?");
                    tview_p.setTextColor(android.graphics.Color.RED);
                }
                if(rbttn_s.isChecked()/* && !rbttn_b.isChecked() && !rbttn_c.isChecked()*/) {
                    tview_p.setText("Would you like the water POKEMON Squirtle?");
                    tview_p.setTextColor(android.graphics.Color.BLUE);
                }
            }
        });


    }

    public void onCheckboxClicked(View view)
    {
        if(cbox_b.isChecked())
        {
            tview_g.setText("Ah yes, a boy");
            tview_g.setTextColor(Color.parseColor("#007DF3"));
            tview_g.setTypeface(Typeface.MONOSPACE);
            tview_g.setAllCaps(false);
        }
        if(cbox_g.isChecked())
        {
            tview_g.setText("As yes, a girl");
            tview_g.setTextColor(android.graphics.Color.MAGENTA);
            tview_g.setTypeface(Typeface.SERIF);
            tview_g.setAllCaps(false);
        }
        if(cbox_b.isChecked() && cbox_g.isChecked())
        {
            tview_g.setText("Not both please");
            tview_g.setTextColor(android.graphics.Color.RED);
            tview_g.setTypeface(Typeface.DEFAULT_BOLD);
            tview_g.setAllCaps(true);
        }
        if(!cbox_b.isChecked() && !cbox_g.isChecked()) {
            tview_g.setText(gender);
            tview_g.setTextColor(android.graphics.Color.GRAY);
            tview_g.setTypeface(Typeface.DEFAULT);
            tview_g.setAllCaps(false);
        }
    }
}
