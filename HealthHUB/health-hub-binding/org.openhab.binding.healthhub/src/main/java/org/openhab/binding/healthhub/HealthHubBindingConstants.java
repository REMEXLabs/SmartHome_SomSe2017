/**
 * Copyright (c) 2014-2016 by the respective copyright holders.
 * All rights reserved. This program and the accompanying materials
 * are made available under the terms of the Eclipse Public License v1.0
 * which accompanies this distribution, and is available at
 * http://www.eclipse.org/legal/epl-v10.html
 */
package org.openhab.binding.healthhub;

import org.eclipse.smarthome.core.thing.ThingTypeUID;

/**
 * The {@link HealthHubBinding} class defines common constants, which are
 * used across the whole binding.
 *
 * @author Eric Schmidt - Initial contribution
 */
public class HealthHubBindingConstants {

    public static final String BINDING_ID = "healthhub";

    // List of all Thing Type UIDs
    public final static ThingTypeUID THING_TYPE_SAMPLE = new ThingTypeUID(BINDING_ID, "user");

    // List of all Channel ids
    public final static String USER_NAME = "userName";
    public final static String USER_HEART_RATE = "userHeartrate";
    public final static String USER_TEMP = "userTemp";
    public final static String USER_STRESS = "userStress";
    public final static String USER_TIMESTAMP = "userTimestamp";
    public final static String USER_ALLOW3RDPARTY = "userAllow3rdParty";

    // Configuration parameters
    public static final String URL = "URL";
}
