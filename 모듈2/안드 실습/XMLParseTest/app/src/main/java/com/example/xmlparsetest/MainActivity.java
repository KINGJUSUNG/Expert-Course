package com.example.xmlparsetest;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.view.InputDevice;
import android.view.View;
import android.widget.Button;
import android.widget.TextView;

import org.w3c.dom.Document;
import org.w3c.dom.Element;
import org.w3c.dom.NamedNodeMap;
import org.w3c.dom.Node;
import org.w3c.dom.NodeList;

import java.io.ByteArrayInputStream;
import java.io.InputStream;

import javax.xml.parsers.DocumentBuilder;
import javax.xml.parsers.DocumentBuilderFactory;

public class MainActivity extends AppCompatActivity {
    private final static String TAG = "MainActivity";
    private TextView mTextView;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        mTextView = findViewById(R.id.textView);
    }

    public void onClickButton(View view) {
        String xmlFile =
                "<?xml version=\"1.0\" encoding=\"utf-8\"?>" +
                  "<order>" +
                    "<item Maker=\"Samsung\" Price=\"23000\">Mouse</item>" +
                    "<item Maker=\"LG\" Price=\"12000\">KeyBoard</item>" +
                    "<item Price=\"156000\" Maker=\"Western Digital\">HDD</item>" +
                  "</order>";

        try {
            InputStream is = new ByteArrayInputStream(xmlFile.getBytes("UTF-8"));

            DocumentBuilderFactory documentBuilderFactory = DocumentBuilderFactory.newInstance();
            DocumentBuilder documentBuilder = documentBuilderFactory.newDocumentBuilder();
            Document document = documentBuilder.parse(is);  // 문서를 트리 형태로 전개합니다.

            // 트리에 접근하기 위해 루트 노드를 얻어옵니다.
            Element root = document.getDocumentElement();

            // 태그의 이름이 item인 노드를 읽어옵니다.
            NodeList itemList = root.getElementsByTagName("item");

            StringBuffer buffer = new StringBuffer();
            for (int i = 0; i < itemList.getLength(); i++) {
                Node item = itemList.item(i);

                Node text = item.getFirstChild();   // 태그의 컨텐트도 자식입니다.
                mTextView.append(text.getNodeValue());

                // 태그의 엘리먼트 속성을 꺼내옵니다.
                NamedNodeMap attrs = item.getAttributes();
                for (int j = 0; j < attrs.getLength(); j++) {
                    Node attr = attrs.item(j);
                    String data = String.format("[%s(%s)]", attr.getNodeName(), attr.getNodeValue());
                    mTextView.append(data + "\n");
                }
            }
        }
        catch (Exception e) {
            e.printStackTrace();
        }
    }
}