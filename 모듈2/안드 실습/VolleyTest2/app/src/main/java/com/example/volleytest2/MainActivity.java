package com.example.volleytest2;

import androidx.appcompat.app.AppCompatActivity;

import android.content.pm.PackageManager;
import android.os.Bundle;
import android.widget.TextView;

import com.android.volley.Request;
import com.android.volley.RequestQueue;
import com.android.volley.Response;
import com.android.volley.VolleyError;
import com.android.volley.toolbox.StringRequest;
import com.android.volley.toolbox.Volley;

import org.w3c.dom.Document;
import org.w3c.dom.Element;
import org.w3c.dom.NodeList;
import org.xmlpull.v1.XmlPullParser;
import org.xmlpull.v1.XmlPullParserFactory;

import java.io.ByteArrayInputStream;
import java.io.InputStream;
import java.io.StringReader;
import java.io.UnsupportedEncodingException;
import java.net.URLEncoder;
import java.util.ArrayList;

import javax.xml.parsers.DocumentBuilder;
import javax.xml.parsers.DocumentBuilderFactory;

public class MainActivity extends AppCompatActivity {
    private final static String TAG = "MainActivity";
    private final static String SERVICE_KEY = "6%2FyD9svJkkQdN13VdF16JIav1kAL1H08kiDZ3qZ%2BByw0iMxUkqGm9jcp04Fo7by1zTOFoeA4JV7RLvo6E08tQg%3D%3D";

    private static RequestQueue requestQueue;
    private TextView mTextView;

    private static class FineDustInfo {
        String dataTime;
        String pm25;    // 초미세먼지 pm 2.5
        String pm10;    // 미세먼지 pm 10
    }
    private ArrayList<FineDustInfo> list = new ArrayList<>();

      // DOM Parser
//    private void parseXML(String xml) {
//        // 자바의 문자열은 유니코드이고 XML은 UTF-8입니다.
//        try {
//            InputStream inputStream = new ByteArrayInputStream(xml.getBytes("UTF-8"));
//
//            DocumentBuilderFactory builderFactory = DocumentBuilderFactory.newInstance();
//            DocumentBuilder builder = builderFactory.newDocumentBuilder();
//            Document document = builder.parse(inputStream);
//            Element root = document.getDocumentElement();
//
//            NodeList items = root.getElementsByTagName("item");
//            for (int i = 0; i < items.getLength(); i++) {
//                NodeList childNodes = items.item(i).getChildNodes();
//
//                // 개행도 하나의 아이템 객체로 인식됩니다.
//                FineDustInfo dustInfo = new FineDustInfo();
//                dustInfo.dataTime = childNodes.item(1).getFirstChild().getNodeValue();
//                dustInfo.pm25 = childNodes.item(17).getFirstChild().getNodeValue();
//                dustInfo.pm10 = childNodes.item(13).getFirstChild().getNodeValue();
//                list.add(dustInfo);
//            }
//        } catch (Exception e) {
//            e.printStackTrace();
//        }
//
//        for (FineDustInfo info: list) {
//            mTextView.append(String.format("time: %s\npm 2.5: %s, pm 10: %s\n\n",
//                    info.dataTime, info.pm25, info.pm10));
//        }
//    }

    // SAX Parser -> XmlPullParser
    private void parseXML(String xml) {
        final int STEP_NONE = 0;        // 태그를 만나지 않았습니다.
        final int STEP_DATATIME = 1;    // dataTime 태그를 만난 경우
        final int STEP_PM25 = 2;        // pm2.5 태그를 만난 경우
        final int STEP_PM10 = 3;        // pm10 태그를 만난 경우

        try {
            XmlPullParserFactory parserFactory = XmlPullParserFactory.newInstance();
            XmlPullParser parser = parserFactory.newPullParser();
            parser.setInput(new StringReader(xml));

            int step = STEP_NONE;
            FineDustInfo dustInfo = null;

            int eventType = parser.getEventType();
            while (eventType != XmlPullParser.END_DOCUMENT) {
                // --------------------------------------------
                switch (eventType) {
                    case XmlPullParser.START_TAG: {
                        String startTag = parser.getName();
                        if (startTag.equals("dataTime")) {
                            step = STEP_DATATIME;
                            dustInfo = new FineDustInfo();
                        }
                        else if (startTag.equals("pm10Value")) { step = STEP_PM10; }
                        else if (startTag.equals("pm25Value")) { step = STEP_PM25; }
                        else { step = STEP_NONE; }
                    } break;
                    case XmlPullParser.TEXT: {
                        String text = parser.getText();
                        switch (step) {
                            case STEP_DATATIME: dustInfo.dataTime = text; break;
                            case STEP_PM10: dustInfo.pm10 = text; break;
                            case STEP_PM25: dustInfo.pm25 = text; break;
                        }
                    } break;
                    case XmlPullParser.END_TAG: {
                        String endTag = parser.getName();
                        if (endTag.equals("pm25Value")) {
                           list.add(dustInfo) ;
                           dustInfo = null;
                        }
                        step = STEP_NONE;
                    } break;
                }
                // --------------------------------------------
                eventType = parser.next();
            }
        } catch (Exception e) {
            e.printStackTrace();
        }

        for (FineDustInfo info: list) {
            mTextView.append(String.format("time: %s\npm 2.5: %s, pm 10: %s\n\n",
                    info.dataTime, info.pm25, info.pm10));
        }
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        mTextView = findViewById(R.id.textView);

        if (requestQueue == null)
            requestQueue = Volley.newRequestQueue(getApplicationContext());
        requestData();
    }

    private void requestData() {
        StringBuilder urlBuilder = new StringBuilder("http://openapi.airkorea.or.kr/openapi/services/rest/ArpltnInforInqireSvc/getMsrstnAcctoRltmMesureDnsty"); /*URL*/
        try {
            urlBuilder.append("?" + URLEncoder.encode("ServiceKey", "UTF-8") + "=" + SERVICE_KEY); /*Service Key*/
            urlBuilder.append("&" + URLEncoder.encode("numOfRows", "UTF-8") + "=" + URLEncoder.encode("10", "UTF-8")); /*한 페이지 결과 수*/
            urlBuilder.append("&" + URLEncoder.encode("pageNo", "UTF-8") + "=" + URLEncoder.encode("1", "UTF-8")); /*페이지 번호*/
            urlBuilder.append("&" + URLEncoder.encode("stationName", "UTF-8") + "=" + URLEncoder.encode("관악구", "UTF-8")); /*측정소 이름*/
            urlBuilder.append("&" + URLEncoder.encode("dataTerm", "UTF-8") + "=" + URLEncoder.encode("DAILY", "UTF-8")); /*요청 데이터기간 (하루 : DAILY, 한달 : MONTH, 3달 : 3MONTH)*/
            urlBuilder.append("&" + URLEncoder.encode("ver", "UTF-8") + "=" + URLEncoder.encode("1.3", "UTF-8")); /*버전별 상세 결과 참고문서 참조*/

            StringRequest request = new StringRequest(Request.Method.GET, urlBuilder.toString(),
                    new Response.Listener<String>() {
                        @Override
                        public void onResponse(String response) {
                            // mTextView.setText(response);
                            parseXML(response);
                        }
                    },
                    new Response.ErrorListener() {
                        @Override
                        public void onErrorResponse(VolleyError error) {
                           mTextView.setText("오류 발생");
                           mTextView.append(error.getMessage());
                        }
                    }
            );

            request.setShouldCache(false);
            requestQueue.add(request);
        }
        catch (Exception e) {
            e.printStackTrace();
        }
    }
}