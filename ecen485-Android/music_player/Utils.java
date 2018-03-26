package com.example.uriahnewkirk.funky_beats;

import android.app.Activity;
import android.content.Intent;

/**
 * Created by uriahnewkirk on 3/3/18.
 */

public class Utils {

    private static int sTheme = 1;
    public final static int THEME_BLUE = 0;
    public final static int THEME_GREEN = 1;
    public final static int THEME_DEFAULT1 = 2;
    public final static int THEME_BLACK = 3;


    public static void changeTheme(Activity act, int theme) {
        sTheme = theme;
        act.finish();
        act.startActivity(new Intent(act, act.getClass()));
    }
    //Change theme in every other activity as well to account for a back button press??

    public static void onActivityCreateSetTheme(Activity act) {
        switch (sTheme) {

            default:
            case THEME_BLUE:
                act.setTheme(R.style.blue_t);
                break;

            case THEME_DEFAULT1:
                act.setTheme(R.style.black_t);
                break;

            case THEME_GREEN:
                act.setTheme(R.style.green_t);
                break;

        }
    }
}
