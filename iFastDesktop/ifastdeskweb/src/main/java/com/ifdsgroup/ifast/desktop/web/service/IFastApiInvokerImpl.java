package com.ifdsgroup.ifast.desktop.web.service;

import java.util.Properties;
import java.util.UUID;

import org.apache.logging.log4j.LogManager;
import org.apache.logging.log4j.Logger;
import org.springframework.stereotype.Repository;
import org.w3c.dom.Document;

import com.ifdsgroup.ifast.desktop.web.exception.DesktopWebSystemException;
import com.ifdsgroup.ifast.desktop.web.service.SmartViewCallService.SrvcType;
import com.ifdsgroup.integration.util.XMLUtil;
import com.ifdsgroup.msg.client.appmsg.auth.AuthException;
import com.ifdsgroup.msg.client.appmsg.auth.AuthResponse;
import com.ifdsgroup.msg.client.appmsg.auth.AuthResponseException;
import com.ifdsgroup.msg.client.appmsg.messenger.Message;
import com.ifdsgroup.msg.client.appmsg.messenger.Messenger;
import com.ifdsgroup.msg.client.appmsg.messenger.MessengerException;
import com.ifdsgroup.msg.client.appmsg.messenger.client.AppMsgClientFactory;

import com.ifdsgroup.ifast.desktop.web.core.config.DesktopWebConstants;


/**
 * This class represents the implementation of functional interface. The
 * behavior can be passed as a method reference to a method. It represents
 * concrete implementation for using Sonic Messenger framework.
 * 
 * @author if993762
 *
 */
@Repository
public class IFastApiInvokerImpl implements IFastApiInvoker{

	private static final Logger LOG = LogManager.getLogger(IFastApiInvokerImpl.class);

	public String apply(String requestXml, String ifastSessionToken, String slotName) throws AuthException {

		Document requestDocument = XMLUtil.parse(requestXml);

		/*
		 * Used for tracking purpose
		 */
		String trackId = UUID.randomUUID().toString();

		/*
		 * Build message properties required by messaging architecture
		 */
		Properties msgProps = new Properties();
		msgProps.setProperty(DesktopWebConstants.IFAST_SESSION_TOKEN, ifastSessionToken);
		msgProps.setProperty(DesktopWebConstants.IFAST_SLOT_NAME, slotName);

		Message msg;

		try {

			/*
			 * Call to Sonic messaging layer
			 */
			// Messenger messager =
			// SonicMessengerSingleton.INSTANCE.getMessenger(slotName,
			// SrvcType.INQUIRY.toString());
			Messenger messenger = AppMsgClientFactory.INSTANCE.getAppMsgClient().getMessenger(slotName,
					SrvcType.INQUIRY.toString());
			msg = messenger.call(requestDocument, msgProps);

			if (msg == null)
				throw new DesktopWebSystemException(
						"No reply message received by JMS Messenger. Possible timeout on message" + trackId);

		} catch (MessengerException me) {
			LOG.debug(me.getMessage(), me);
			throw new DesktopWebSystemException(me.getMessage(), me.getCause());
		}

		/*
		 * Get the XML data from the back-end API
		 */
		Document responseDocument = msg.getContentAsXml();

		/*
		 * Validate whether the authorized entity can access data
		 */
		AuthResponse authResp = AuthResponse.forDocument(responseDocument);
		if (authResp != null && authResp.hasRejectedStatus()) {
			throw new AuthResponseException("Authorization rejected on message " + trackId + ".", authResp);
		}

		LOG.debug("Core response from progress : " + msg.getContent());
		return msg.getContent();

	}

}