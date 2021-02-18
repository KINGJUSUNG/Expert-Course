package com.example.locationtest;

import androidx.annotation.NonNull;
import androidx.annotation.Nullable;
import androidx.appcompat.app.AlertDialog;
import androidx.appcompat.app.AppCompatActivity;
import androidx.core.app.ActivityCompat;
import androidx.core.content.ContextCompat;

import android.Manifest;
import android.content.Context;
import android.content.DialogInterface;
import android.content.Intent;
import android.content.pm.PackageManager;
import android.location.Location;
import android.location.LocationListener;
import android.location.LocationManager;
import android.os.Bundle;
import android.os.LocaleList;
import android.provider.Settings;
import android.view.ContextThemeWrapper;
import android.widget.TextView;
import android.widget.Toast;

public class MainActivity extends AppCompatActivity {
    private final static String TAG = "MainActivity";
    public final static int REQUEST_CODE_GPS_ENABLE = 0;

    private TextView mLoationTextView;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        mLoationTextView = findViewById(R.id.locationTextView);

        // GPS 기능이 활성화되어 있는지를 확인합니다.
        if (!isLocationServiceEnabled())
            showDialogForLocationServiceSetting();

        // 위치 접근 권한이 설정되어 있는지를 확인합니다.
        if (!isLocationPermissionAllowed())
            requestLocationPermission();
        else
            requestLocation();
    }

    private void requestLocation() {
        LocationManager locationManager = (LocationManager)getSystemService(Context.LOCATION_SERVICE);
        try {
            long minTime = 0;       // 수신 주기: ms단위로 입력
            float minDistance = 1;   // 거리 변화: m(미터) 단위로 입력
            locationManager.requestLocationUpdates(LocationManager.GPS_PROVIDER, minTime, minDistance,
                    new LocationListener() {
                        @Override
                        public void onLocationChanged(@NonNull Location location) {
                            double latitude = location.getLatitude();
                            double longitude = location.getLongitude();
                            String coordinate = String.format("위도: %f\n경도: %f", latitude, longitude);
                            mLoationTextView.setText(coordinate);
                        }
                    });
        }
        catch (SecurityException e) {
            e.printStackTrace();
        }
    }


    private boolean isLocationPermissionAllowed() {
        int hasFineLocationPermission = ContextCompat.checkSelfPermission(MainActivity.this,
                Manifest.permission.ACCESS_FINE_LOCATION);
        return hasFineLocationPermission == PackageManager.PERMISSION_GRANTED;
    }

    private void requestLocationPermission() {
        ActivityCompat.requestPermissions(MainActivity.this,
                new String[] { Manifest.permission.ACCESS_FINE_LOCATION},
                REQUEST_CODE_GPS_ENABLE);
    }

    @Override
    public void onRequestPermissionsResult(int requestCode, @NonNull String[] permissions, @NonNull int[] grantResults) {
        super.onRequestPermissionsResult(requestCode, permissions, grantResults);
        switch (requestCode) {
            case REQUEST_CODE_GPS_ENABLE:
                for (int i = 0; i < permissions.length; i++) {
                    String permission = permissions[i];
                    int grantResult = grantResults[i];

                    if (permission.equals(Manifest.permission.ACCESS_FINE_LOCATION)) {
                        if (grantResult == PackageManager.PERMISSION_GRANTED) {
                            // 앱을 사용하는 동안만 허용
                        }
                        else if (grantResult == PackageManager.PERMISSION_DENIED) {
                            // 거부한 경우
                            Toast.makeText(MainActivity.this, "이 앱은 위치 권한이 필요합니다.",
                                    Toast.LENGTH_LONG).show();
                        }
                    }
                }
                break;
        }
    }

    private boolean isLocationServiceEnabled() {
        LocationManager manager = (LocationManager)getSystemService(LOCATION_SERVICE);
        return manager.isProviderEnabled(LocationManager.GPS_PROVIDER);
    }

    private void showDialogForLocationServiceSetting() {
        AlertDialog.Builder builder = new AlertDialog.Builder(MainActivity.this);
        builder.setTitle("위치 서비스 활성화");
        builder.setMessage("현재 앱은 위치 서비스가 필요합니다. 위치 서비스를 설정하시겠습니까?");

        builder.setPositiveButton("예", new DialogInterface.OnClickListener() {
            @Override
            public void onClick(DialogInterface dialogInterface, int i) {
                Intent locationSettingIntent = new Intent(Settings.ACTION_LOCATION_SOURCE_SETTINGS);
                startActivityForResult(locationSettingIntent, REQUEST_CODE_GPS_ENABLE);
            }
        });

        builder.setNegativeButton("아니오", new DialogInterface.OnClickListener() {
            @Override
            public void onClick(DialogInterface dialogInterface, int i) {
                Toast.makeText(MainActivity.this, "위치 설정을 해야 합니다.", Toast.LENGTH_LONG).show();
                dialogInterface.cancel();
            }
        });
        builder.create().show();
    }

    @Override
    protected void onActivityResult(int requestCode, int resultCode, @Nullable Intent data) {
        super.onActivityResult(requestCode, resultCode, data);

        switch (requestCode) {
            case REQUEST_CODE_GPS_ENABLE:
                if (!isLocationServiceEnabled()) {
                    Toast.makeText(this, "위치 설정을 하지 않았습니다.", Toast.LENGTH_LONG).show();
                }
                break;
        }

    }
}












