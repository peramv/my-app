package com.ifdsgroup.pdf;

import java.security.InvalidKeyException;
import java.security.NoSuchAlgorithmException;
import java.util.Date;
import java.util.HashMap;
import java.util.Map;
import java.util.Properties;

import javax.crypto.Mac;
import javax.crypto.spec.SecretKeySpec;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpSession;

import org.apache.commons.codec.binary.Base64;
import org.apache.http.client.methods.CloseableHttpResponse;
import org.apache.http.client.methods.HttpPost;
import org.apache.http.entity.ContentType;
import org.apache.http.entity.StringEntity;
import org.apache.http.entity.mime.MultipartEntityBuilder;
import org.apache.http.impl.client.CloseableHttpClient;
import org.apache.http.impl.client.HttpClients;
import org.apache.http.util.EntityUtils;
import org.apache.logging.log4j.LogManager;
import org.apache.logging.log4j.Logger;
import org.dom4j.DocumentHelper;
import org.dom4j.Element;
import org.dom4j.XPath;
import org.json.simple.JSONObject;
import org.json.simple.parser.JSONParser;

import com.ifdsgroup.msg.client.appmsg.messenger.Message;
import com.ifdsgroup.msg.client.appmsg.messenger.Messenger;
import com.ifdsgroup.msg.client.appmsg.messenger.client.AppMsgClientFactory;

public class SmartPDFAWDUtil {

	/*
	 * Logger to log any errors/issues in the log file
	 */
	private static final Logger LOG = LogManager.getLogger(SmartPDFAWDUtil.class);

	private String _serviceType;
	private String _awdWorkType;
	private XPath _awdObjXpath;
	private XPath _awdSourceXpath;

	// B2BSignature
	private static final String sep = ":";
	private static final String ALGORITHM = "HmacSHA512";

	/************* Constructor *****************/
	public SmartPDFAWDUtil(String awdWorkType, XPath awdObjXpath, XPath awdSourceXpath, String serviceType) {
		_awdWorkType = awdWorkType;
		_awdObjXpath = awdObjXpath;
		_awdSourceXpath = awdSourceXpath;
		_serviceType = serviceType;
	}

	/************* private methods *****************/

	private static HashMap<String, String> getFieldValues(HttpServletRequest request) {
		HashMap<String, String> map = new HashMap<String, String>();

		map.put("ACCT", request.getParameter("account"));
		map.put("NAMO", request.getParameter("faxName"));
		map.put("FAXO", request.getParameter("faxNum"));
		map.put("EMAL", request.getParameter("emailAddr"));
		map.put("RCPT", request.getParameter("RCPT"));

		return map;
	}

	private static String buildFieldValuesXML(HashMap<String, String> fieldValues) {
		String xml = "<fieldValues>";

		Map<String, String> map = fieldValues;
		for (Map.Entry<String, String> entry : map.entrySet()) {
			String key = entry.getKey();
			String value = entry.getValue();

			if (value != "") {
				xml += "<fieldValue name=\"" + key + "\">";
				xml += "<value>" + value + "</value>";
				xml += "</fieldValue>";
			}
		}

		xml += "</fieldValues>";

		return xml;
	}

	private String getB2BSignature(JSONObject awdProp) {
		String awdB2BSignatureKey = awdProp.get("B2BSigning_Key").toString();
		String awdUser = awdProp.get("awdUserId").toString();
		Date date = new Date();

		return signB2BSignature(awdB2BSignatureKey, awdUser, date);
	}

	private static String signB2BSignature(String secret, String userID, Date time) {
		String message = Long.toString(time.getTime()) + sep + userID;
		String hash = "";
		Mac hmac;

		try {
			hmac = Mac.getInstance(ALGORITHM);
			SecretKeySpec secret_key = new SecretKeySpec(secret.getBytes(), ALGORITHM);
			hmac.init(secret_key);
			hash = new String(Base64.encodeBase64(hmac.doFinal(message.getBytes())));
		} catch (NoSuchAlgorithmException e) {
			LOG.error(e.getMessage(), e);
		} catch (InvalidKeyException e) {
			LOG.error(e.getMessage(), e);
		}

		return hash + sep + message;
	}

	/************* public methods *****************/

	public String createAWDObj(HttpServletRequest request) {
		LOG.info("SmartPDFAWDUtil - sending AWD request to create work object");

		JSONObject awdProp = getAWDConnectionProp(request.getParameter("envName"), request.getParameter("sessionId"));
		String awdHost = awdProp.get("wsURL").toString();
		String awdBusArea = awdProp.get("businessArea").toString();
		String awdUser = awdProp.get("awdUserId").toString();
		HashMap<String, String> fieldValues = getFieldValues(request);

		String awdObjId = null;
		CloseableHttpClient httpClient = HttpClients.createDefault();
		HttpPost httpPost = new HttpPost(awdHost + "/b2b/services/v1/instances");
		httpPost.addHeader("Content-Type", "application/vnd.dsttechnologies.awd+xml");
		httpPost.addHeader("REMOTE_USER", awdUser);
		httpPost.addHeader("B2BSignature", getB2BSignature(awdProp));
		String requestXml = "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"yes\"?>"
				+ "<createInstances xmlns=\"http://www.dsttechnologies.com/awd/rest/v1\">" + "<createInstance>"
				+ "<assignTo>" + awdUser + "</assignTo>" + "<businessAreaName>" + awdBusArea + "</businessAreaName>"
				+ "<typeName>" + _awdWorkType + "</typeName>" + "<statusName>CREATED</statusName>"
				+ buildFieldValuesXML(fieldValues)
				+ "<addComment>Work object created via iFAST/Desktop SmartPDF service</addComment>"
				+ "</createInstance>" + "</createInstances>";
		LOG.info("SmartPDFAWDUtil - CreateObj AWD API requestXml:\n" + requestXml);

		String responseXml = null;
		try {
			httpPost.setEntity(new StringEntity(requestXml));
			CloseableHttpResponse httpResponse = httpClient.execute(httpPost);
			responseXml = EntityUtils.toString(httpResponse.getEntity());
			LOG.info("SmartPDFAWDUtil - CreateObj AWD API responseXml:\n " + responseXml);
		} catch (Exception e) {
			e.printStackTrace();
			LOG.error(e.getMessage(), e);
		}

		try {
			Element awdObjEl = (Element) _awdObjXpath.selectSingleNode(DocumentHelper.parseText(responseXml));
			awdObjId = awdObjEl.valueOf("@id");
		} catch (Exception e) {
			e.printStackTrace();
			LOG.error(e.getMessage(), e);
		}
		return awdObjId;
	}

	public String createAWDSource(HttpServletRequest request, String awdObjId) {
		LOG.info("SmartPDFAWDUtil - sending AWD request to create source object");

		JSONObject awdProp = getAWDConnectionProp(request.getParameter("envName"), request.getParameter("sessionId"));
		String awdHost = awdProp.get("wsURL").toString();
		String awdBusArea = awdProp.get("businessArea").toString();
		String awdUser = awdProp.get("awdUserId").toString();

		HttpSession session = request.getSession();
		byte[] pdfDoc = (byte[]) session.getAttribute("pdfDoc");
		String pdfName = (String) session.getAttribute("pdfName");

		String awdSourceId = null;
		CloseableHttpClient httpClient = HttpClients.createDefault();
		HttpPost httpPost = new HttpPost(awdHost + "/b2b/services/v1/instances");
		httpPost.addHeader("REMOTE_USER", awdUser);
		httpPost.addHeader("B2BSignature", getB2BSignature(awdProp));
		String requestXml = "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"yes\"?>"
				+ "<createSourceInstance xmlns=\"http://www.dsttechnologies.com/awd/rest/v1\">" + "<businessAreaName>"
				+ awdBusArea + "</businessAreaName>" + "<typeName>GDL</typeName>" + "<createRelationships>"
				+ "<parentIds>" + awdObjId + "</parentIds>" + "</createRelationships>" + "<fieldValues>"
				+ "<fieldValue name=\"EXT\">" + "<value>PDF</value>" + "</fieldValue>" + "</fieldValues>"
				+ "</createSourceInstance>";
		LOG.info("SmartPDFAWDUtil - CreateSource AWD API requestXml:\n" + requestXml);

		String responseXml = null;

		try {
			MultipartEntityBuilder builder = MultipartEntityBuilder.create();
			builder.addTextBody("request", requestXml, ContentType.create("application/vnd.dsttechnologies.awd+xml"));
			builder.addBinaryBody("file_input", pdfDoc, ContentType.create("application/pdf"), pdfName);
			httpPost.setEntity(builder.build());
			CloseableHttpResponse httpResponse = httpClient.execute(httpPost);
			awdSourceId = EntityUtils.toString(httpResponse.getEntity());
			LOG.info("SmartPDFAWDUtil - CreateSource AWD API responseXml:\n" + awdSourceId);
		} catch (Exception e) {
			e.printStackTrace();
			LOG.error("SmartPDFAWDUtil - exception occurred sending AWD API request: " + e.getMessage(), e);
		}

		return awdSourceId;
	}

	public JSONObject getAWDConnectionProp(String envName, String sessionId) {

		/**
		 * Fuse Changes: commented the below code
		 */
		// Producer producer = null;

		Properties msgProperties = new Properties();
		JSONParser parser = new JSONParser();
		JSONObject awdProp = null;

		try {

			/**
			 * Fuse Changes: commented the below code
			 */
			// producer = _producerMap.getProducer(envName, _serviceType);
			// msgProperties =
			// _msgConfig.getEnvConfig(envName).getMsgAttributes();

			msgProperties.put("IFAST_SESSION_TOKEN", sessionId);
			msgProperties.put("IFAST_ORIGIN_APPLICATION", "DWEB");
			msgProperties.setProperty("IFAST_SLOT_NAME", envName);

			String requestJSON = "{\"CompanyId\":\"" + envName + "\", \"RequestType\":\"Info\"}";
			LOG.info(_serviceType + " request: " + requestJSON);

			/**
			 * Fuse Changes: commented the below code
			 */
			// String responseJSON = producer.sendReceive(requestJSON,
			// msgProperties, _timeToLive);

			Messenger messenger = AppMsgClientFactory.INSTANCE.getAppMsgClient().getMessenger(envName, _serviceType);
			Message message = messenger.call(requestJSON, msgProperties);
			String responseJSON = message.getContent();

			LOG.info(_serviceType + " response: " + responseJSON);
			awdProp = (JSONObject) parser.parse(responseJSON);
		} catch (Exception e) {
			e.printStackTrace();
			LOG.error(e.getMessage(), e);
		}

		if (awdProp.get("wsURL") == null || awdProp.get("businessArea") == null || awdProp.get("awdUserId") == null) {
			LOG.error(
					"SmartPDFAWDUtil - unable to obtain AWD connection properties from " + _serviceType + " response");
		}

		return awdProp;
	}
}