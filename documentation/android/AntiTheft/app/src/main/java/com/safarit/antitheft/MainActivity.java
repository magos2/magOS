package com.safarit.antitheft;

import android.app.ListActivity;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.Menu;
import android.view.MenuInflater;
import android.view.View;
import android.widget.AdapterView;
import android.widget.ArrayAdapter;
import android.widget.ListView;
import android.widget.Toast;

public class MainActivity extends ListActivity {

    ListView listview;



    String[] countries = new String[] {

            "Samsung",
            "Nokia",
            "Blackberyy",
    };

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        //setContentView(R.layout.activity_main);
        // Declaring ArrayAdapter for the default listview
        listview = getListView();
        ArrayAdapter<String> listadapter = new ArrayAdapter<String>(this, android.R.layout.simple_list_item_1,countries);
        // Setting ArrayAdapter for the default listview
        listview.setAdapter(listadapter);
        // Defining ItemClick event Listener

        // OnItemClickListener listener = new OnItemClickListener() {

        // This method will be triggered when an item in the listview is clicked ( or touched )
        listview.setOnItemClickListener(new AdapterView.OnItemClickListener() {
            @Override
            public void onItemClick(AdapterView<?> adapterView, View view, int i, long l) {

                Toast.makeText(getBaseContext(), "You selected : " + countries[i], Toast.LENGTH_SHORT).show();
            }
        });

        // Setting an ItemClickEvent Listener for the listview

        // In this example we are making use the default listview

        //     getListView().setOnItemClickListener(listener);
    }

    @Override
    public boolean onCreateOptionsMenu(Menu menu)
    {
        MenuInflater inflater = getMenuInflater();
        inflater.inflate(R.menu.menu, menu);
        return true;
    }
}
