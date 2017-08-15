/**
 * Copyright (c) 2014-2016 by the respective copyright holders.
 * All rights reserved. This program and the accompanying materials
 * are made available under the terms of the Eclipse Public License v1.0
 * which accompanies this distribution, and is available at
 * http://www.eclipse.org/legal/epl-v10.html
 */
package org.openhab.binding.healthhub.handler;

import java.math.BigDecimal;
import java.text.SimpleDateFormat;
import java.util.Date;
import java.util.concurrent.ScheduledFuture;
import java.util.concurrent.TimeUnit;

import org.eclipse.smarthome.config.core.Configuration;
import org.eclipse.smarthome.core.library.types.OnOffType;
import org.eclipse.smarthome.core.library.types.StringType;
import org.eclipse.smarthome.core.thing.Channel;
import org.eclipse.smarthome.core.thing.ChannelUID;
import org.eclipse.smarthome.core.thing.Thing;
import org.eclipse.smarthome.core.thing.ThingStatus;
import org.eclipse.smarthome.core.thing.binding.BaseThingHandler;
import org.eclipse.smarthome.core.types.Command;
import org.eclipse.smarthome.core.types.RefreshType;
import org.eclipse.smarthome.core.types.State;
import org.openhab.binding.healthhub.HealthHubBindingConstants;
import org.openhab.binding.healthhub.utils.HealthHubJsonParser;
import org.openhab.binding.healthhub.utils.HealthHubUser;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

/**
 * The {@link HealthHubHandler} is responsible for handling commands, which are
 * sent to one of the channels.
 *
 * @author Eric Schmidt - Initial contribution
 */
public class HealthHubHandler extends BaseThingHandler {

    private Logger logger = LoggerFactory.getLogger(HealthHubHandler.class);
    private BigDecimal refresh;

    private HealthHubJsonParser jsonParser;
    String configURL;
    HealthHubUser currentUser;

    ScheduledFuture<?> refreshJob;

    public HealthHubHandler(Thing thing) {
        super(thing);
    }

    @Override
    public void handleCommand(ChannelUID channelUID, Command command) {
        if (command instanceof RefreshType) {
            fetchUserInformation();

            for (Channel channel : getThing().getChannels()) {
                updateChannel(channel.getUID().getId());
            }
        }
    }

    @Override
    public void initialize() {
        super.initialize();

        checkConfiguration();

        jsonParser = new HealthHubJsonParser(configURL);
        refresh = new BigDecimal(2);

        startAutomaticRefresh();
    }

    /**
     * This method checks if the provided configuration is valid.
     * When invalid parameter is found, default value is assigned.
     */
    private void checkConfiguration() {
        logger.debug("Start reading HealthHub Thing configuration.");
        Configuration configuration = getConfig();

        // It is not necessary to check if the URL is valid, this will be done in fetchFeedData() method
        configURL = (String) configuration.get(HealthHubBindingConstants.URL);
    }

    private void startAutomaticRefresh() {
        Runnable runnable = new Runnable() {
            @Override
            public void run() {
                try {
                    boolean success = fetchUserInformation();
                    if (success) {
                        for (Channel channel : getThing().getChannels()) {
                            updateChannel(channel.getUID().getId());
                        }

                        updateStatus(ThingStatus.ONLINE);
                    }
                } catch (Exception e) {
                    logger.debug("Exception occurred during execution: {}", e.getMessage(), e);
                }
            }
        };

        refreshJob = scheduler.scheduleAtFixedRate(runnable, 0, refresh.intValue(), TimeUnit.SECONDS);
    }

    public boolean fetchUserInformation() {
        currentUser = jsonParser.getUserInformation();

        if (currentUser != null) {
            return true;
        }

        return false;
    }

    public void updateChannel(String channelID) {
        if (isLinked(channelID)) {
            updateState(channelID, getStateByChannel(channelID));
        }
    }

    public State getStateByChannel(String channelID) {
        switch (channelID) {
            case HealthHubBindingConstants.USER_NAME:
                return new StringType(currentUser.getFullName());
            case HealthHubBindingConstants.USER_HEART_RATE:
                return new StringType(currentUser.getPulse() + " bpm");
            case HealthHubBindingConstants.USER_TEMP:
                return new StringType(currentUser.getTemp() + " °C");
            case HealthHubBindingConstants.USER_STRESS:
                return new StringType(currentUser.getStress());
            case HealthHubBindingConstants.USER_TIMESTAMP:
                Date lastScan = currentUser.getScanDate();
                SimpleDateFormat formatDate = new SimpleDateFormat("EEEE, HH:mm");
                return new StringType(formatDate.format(lastScan));
            case HealthHubBindingConstants.USER_ALLOW3RDPARTY:
                if (currentUser.isThirdPartyAccess()) {
                    return OnOffType.ON;
                }
                return OnOffType.OFF;
        }

        return null;
    }
}
