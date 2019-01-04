package com.ifdsgroup.ifast.desktop.web.service;

import static com.ifdsgroup.ifast.desktop.web.core.config.DesktopWebConstants.FAILURE_RESPONSE;
import static com.ifdsgroup.ifast.desktop.web.core.config.DesktopWebConstants.SONIC_RESPONSE_REJECTED;
import static com.ifdsgroup.ifast.desktop.web.core.config.DesktopWebConstants.SONIC_RESPONSE_SUCCESS;
import static com.ifdsgroup.ifast.desktop.web.core.config.DesktopWebConstants.SUCCESS_RESPONSE;
import static com.ifdsgroup.ifast.desktop.web.xpath.util.XPathUtil.nodeToString;

import org.apache.logging.log4j.LogManager;
import org.apache.logging.log4j.Logger;

import com.ifdsgroup.ifast.desktop.web.dto.SmartViewPayload;
import com.ifdsgroup.msg.client.appmsg.auth.AuthException;
import com.ifdsgroup.msg.client.appmsg.auth.AuthResponseException;

/**
 *
 * This interface is a functional interface for accessing the back-end API. The
 * different implementations can be passed at runtime making the code more
 * scalable.
 *
 * @author if993762
 *
 */
@FunctionalInterface
public interface IFastApiInvoker {

	/**
	 * Functional method which will represent different dynamic implementations
	 *
	 * @param data
	 * @param token
	 * @param slotName
	 * @return
	 * @throws AuthException
	 */
	String apply(String data, String token, String slotName) throws AuthException;

	/**
	 * Static method to handle checked exceptions while different
	 * implementations are called to access back-end API
	 *
	 * @param function
	 * @param data
	 * @param token
	 * @param slotName
	 * @return
	 */
	static SmartViewPayload handlingChecked(IFastApiInvoker function, String data, String token, String slotName,
			String ignoreErrorCode) {

		String response = null;
		String responseStatus = null;
		String responseMsg = null;

		try {

			/*
			 * Call to the functional interface method with dynamic
			 * implementations being passed as a function
			 */
			response = function.apply(data, token, slotName);

			String sonicResponseStatus = SmartViewCallService.getSonicResponseStatus(response);
			if (SONIC_RESPONSE_SUCCESS.equals(sonicResponseStatus)) {

				String errors = nodeToString(SmartViewCallService.getErrorsNode(response));
				responseStatus = SUCCESS_RESPONSE;

				if (errors != null && !"".equals(errors))
					responseMsg = errors;
				else
					responseMsg = "<Errors></Errors>";

			} else if (SONIC_RESPONSE_REJECTED.equals(sonicResponseStatus)) {
				String errors = nodeToString(SmartViewCallService.getErrorsNode(response));
				if (ignoreErrorCode != null && SmartViewCallService.getErrorCode(errors).equals(ignoreErrorCode)) {
					responseStatus = SUCCESS_RESPONSE;
					responseMsg = "<Errors></Errors>";
				} else {
					responseMsg = errors;
					responseStatus = FAILURE_RESPONSE;
				}
			} else { // This is a temporary placeholder unit it is determined if
						// the sonic response status can be anything other than
						// "Accepted" or "Rejected"
				responseStatus = FAILURE_RESPONSE;
				responseMsg = "Something went wrong here";
			}

		} catch (AuthResponseException aRE) {
			LogHolder.getLogger().debug(aRE.getMessage(), aRE);
			responseStatus = FAILURE_RESPONSE;
			responseMsg = aRE.getMessage();
		} catch (AuthException aE) {
			LogHolder.getLogger().debug(aE.getMessage(), aE);
			responseStatus = FAILURE_RESPONSE;
			StringBuilder errorMsgBuilder = new StringBuilder();
			errorMsgBuilder.append("<Errors><Error><errorSeverity>error</errorSeverity><type>environment</type><text>")
					.append("View call to ").append(slotName)
					.append(" failed and/or timed out.</text></Error></Errors>");
			responseMsg = errorMsgBuilder.toString();
		}

		return new SmartViewPayload(response, responseStatus, responseMsg);

	}

}

/*
 * This class is required to hold the logger for IFastApiInvoker because
 * IFastApiInvoker is a functional interface
 */
final class LogHolder {
	private static final Logger LOG = LogManager.getLogger(IFastApiInvoker.class);

	private LogHolder() {
	}

	public static Logger getLogger() {
		return LOG;
	}
}
