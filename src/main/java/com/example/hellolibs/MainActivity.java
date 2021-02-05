/*
 * Copyright (C) 2019 Technexion Ltd.
 *
 * Author: Wig Cheng <wig.cheng@technexion.com>
 * 
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
package com.example.hellolibs;

import android.app.Activity;
import android.os.Bundle;
import android.widget.RelativeLayout;
import android.widget.RelativeLayout.LayoutParams;
import android.widget.TextView;
import android.view.View;
import android.widget.AdapterView;
import android.widget.ArrayAdapter;
import android.widget.Spinner;
import android.widget.Toast;
import android.widget.Button;
import android.widget.EditText;
/*
 * Simple Java UI to trigger jni function. It is exactly same as Java code
 * in hello-jni.
 */
public class MainActivity extends Activity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        Spinner gpio_bank_spinner = (Spinner) findViewById(R.id.spinner_gpio_bank);
        Spinner gpio_line_spinner = (Spinner) findViewById(R.id.spinner_gpio_line);
        TextView gpiod_version_tv = (TextView)findViewById(R.id.text_libgpiod_version);
        TextView gpio_output_tv = (TextView)findViewById(R.id.text_gpio_output);
        Button gpio_get_button = (Button)findViewById(R.id.button_gpio_get);
        Button gpio_set_button = (Button)findViewById(R.id.button_gpio_set);
        EditText gpio_set_value = (EditText)findViewById(R.id.edit_gpio_set_value);

        ArrayAdapter<CharSequence> bank_adapter = ArrayAdapter.createFromResource(
        this, R.array.gpiobank_array, android.R.layout.simple_spinner_item);
        bank_adapter.setDropDownViewResource(android.R.layout.simple_spinner_dropdown_item);
        gpio_bank_spinner.setAdapter(bank_adapter);

        ArrayAdapter<CharSequence> line_adapter = ArrayAdapter.createFromResource(
            this, R.array.gpioline_array, android.R.layout.simple_spinner_item);
            line_adapter.setDropDownViewResource(android.R.layout.simple_spinner_dropdown_item);
            gpio_line_spinner.setAdapter(line_adapter);

        gpiod_version_tv.setText("liggpiod revision:" + stringFromJNI());

        gpio_get_button.setOnClickListener(new View.OnClickListener() {
            public void onClick(View v) {
                int gpionum_bank = gpio_bank_spinner.getSelectedItemPosition() - 1;
                int gpionum_line = gpio_line_spinner.getSelectedItemPosition() - 1;
                gpio_output_tv.setText("Output: " + getGpioInfo(gpionum_bank, gpionum_line));
            }
        });

        gpio_set_button.setOnClickListener(new View.OnClickListener() {
            public void onClick(View v) {
                int gpionum_bank = gpio_bank_spinner.getSelectedItemPosition() - 1;
                int gpionum_line = gpio_line_spinner.getSelectedItemPosition() - 1;
                String value_text = gpio_set_value.getText().toString();
                if (value_text.equals("")) {
                   gpio_output_tv.setText("Please set value, 1 is pull high, 0 is pull low");
               } else {
                  int gpionum_set_value = Integer.parseInt(value_text);
                  gpio_output_tv.setText("Output: " + setGpioInfo(gpionum_bank, gpionum_line, gpionum_set_value));
                }
            }
        });
    }
    public native String  stringFromJNI();
    public native String  getGpioInfo(int gpiobank,int gpioline);
    public native String  setGpioInfo(int gpiobank,int gpioline, int value);
    static {
        System.loadLibrary("gpiod_jni");
    }

}
