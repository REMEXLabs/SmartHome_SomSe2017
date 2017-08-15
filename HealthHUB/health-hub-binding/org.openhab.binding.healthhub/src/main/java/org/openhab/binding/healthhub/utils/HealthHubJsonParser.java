package org.openhab.binding.healthhub.utils;

import java.io.IOException;
import java.net.URL;
import java.net.URLConnection;

import org.apache.commons.io.IOUtils;

import com.google.gson.Gson;
import com.google.gson.GsonBuilder;

public class HealthHubJsonParser {
    private Gson gson;
    private String url;

    public HealthHubJsonParser(String url) {
        gson = new GsonBuilder().setDateFormat("yyyy-MM-dd'T'HH:mm:ssZ").create();
        this.url = url;
    }

    public HealthHubUser getUserInformation() {
        return parseJson();
    }

    private HealthHubUser parseJson() {
        HealthHubUser result = null;

        try {
            // "http://localhost:3000/getData"
            URL url = new URL(this.url);
            URLConnection connection = url.openConnection();

            try {
                String response = IOUtils.toString(connection.getInputStream());

                // Map the JSON response to an object
                result = gson.fromJson(response, HealthHubUser.class);
            } finally {
                IOUtils.closeQuietly(connection.getInputStream());
            }
        } catch (IOException | IllegalStateException e) {
            String errorMsg = e.getMessage();
        }
        return result;
    }
}
