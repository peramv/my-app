package com.ifdsgroup.ifast.desktop.web.service;

import java.io.File;
import java.io.IOException;
import java.util.HashMap;
import java.util.Properties;

import javax.servlet.ServletConfig;
import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;

import org.apache.logging.log4j.LogManager;
import org.apache.logging.log4j.Logger;
import org.dom4j.DocumentHelper;
import org.dom4j.XPath;
import org.jaxen.SimpleNamespaceContext;
import org.json.simple.JSONObject;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.beans.factory.config.AutowireCapableBeanFactory;
import org.springframework.web.context.WebApplicationContext;
import org.springframework.web.context.support.WebApplicationContextUtils;

import com.ifdsgroup.ifast.desktop.web.core.config.ServicesConfiguration;
import com.ifdsgroup.msg.client.appmsg.SonicProducerMap;
import com.ifdsgroup.msg.client.appmsg.config.MsgConfig;
import com.ifdsgroup.pdf.SmartPDF;
import com.ifdsgroup.pdf.SmartPDFAWDUtil;

public class SmartPDFService extends HttpServlet {

	/*
	 * Logger to log any errors/issues in the log file
	 */
	private static final Logger LOG = LogManager.getLogger(SmartPDFService.class);

	private MsgConfig msgConfig;
	private SonicProducerMap producerMap;

	// SmartPDF library properties
	private String dataPath;
	private String commonDirectory;
	private String configDirectory;
	private String imageDirectory;
	private String resourcesDirectory;
	private String decimalDelimitorEn;
	private String decimalDelimitorFr;

	private String serviceType;
	private long timeToLive;
	private String awdWorkType;

	// PDF request parameters
	private String clientId;
	private String formType;
	private String locale;

	private XPath awdObjXpath;
	private XPath awdSourceXpath;

	private SmartPDFAWDUtil smartPDFAWDUtil;

	private WebApplicationContext springContext;

	@Autowired
	private ServicesConfiguration servicesConfig;

	@Override
	public void init(final ServletConfig config) throws ServletException {

		LOG.info("SmartPDFService - init");

		/*
		 * Required to autowire the servicesConfig bean
		 */
		super.init(config);
		springContext = WebApplicationContextUtils.getRequiredWebApplicationContext(config.getServletContext());
		final AutowireCapableBeanFactory beanFactory = springContext.getAutowireCapableBeanFactory();
		beanFactory.autowireBean(this);

		initSmartPDFProp();

		HashMap<String, String> map = new HashMap<String, String>();
		map.put("dst", "http://www.dsttechnologies.com/awd/rest/v1");
		awdObjXpath = DocumentHelper.createXPath("//dst:instance");
		awdObjXpath.setNamespaceContext(new SimpleNamespaceContext(map));
		awdSourceXpath = DocumentHelper.createXPath("//dst:sourceInstance");
		awdSourceXpath.setNamespaceContext(new SimpleNamespaceContext(map));

		smartPDFAWDUtil = new SmartPDFAWDUtil(awdWorkType, awdObjXpath, awdSourceXpath, serviceType);
	}

	private void initSmartPDFProp() {

		Properties props = servicesConfig.getProperties();

		// dataPath = props.getProperty("pdf.data.path");
		dataPath = System.getProperty("pdf.data.path");
		commonDirectory = props.getProperty("pdf.common.directory");
		configDirectory = props.getProperty("pdf.config.directory");
		imageDirectory = props.getProperty("pdf.image.directory");
		resourcesDirectory = props.getProperty("pdf.resource.directory");
		decimalDelimitorEn = props.getProperty("pdf.decimalDelimEn");
		decimalDelimitorFr = props.getProperty("pdf.decimalDelimFr");
		awdWorkType = props.getProperty("pdf.msg.config.awd.work.type");
		serviceType = props.getProperty("pdf.msg.config.service.type");
	}

	private void generatePDFService(HttpServletRequest request, HttpServletResponse response) {
		LOG.info("SmartPDFService - generatePDFService request");

		HttpSession session = request.getSession();
		clientId = request.getParameter("clientId").toLowerCase();
		formType = request.getParameter("formType");
		locale = request.getParameter("locale").substring(0, 2);

		String taxDataXML = request.getParameter("taxDataXML");

		SmartPDF sPDF = new SmartPDF(this,
				"<?xml version='1.0' encoding='ISO-8859-1'?><root><SmartView>" + taxDataXML + "</SmartView></root>");
		byte[] pdfDoc = null;
		String pdfName = null;

		try {
			pdfDoc = sPDF.generate();
			pdfName = buildPDFName(clientId, formType, request.getParameter("taxYear"));
		} catch (Exception e) {
			LOG.error("SmartPDFService - exception occurred generating pdf: " + e.getMessage());
			e.printStackTrace();
		}

		session.setAttribute("pdfDoc", pdfDoc);
		session.setAttribute("pdfName", pdfName);

		try {
			response.setContentType("application/pdf");
			response.setHeader("Pragma", "public");
			response.setHeader("Cache-Control", "max-age=0");
			response.setContentLength(pdfDoc.length);
			response.getOutputStream().write(pdfDoc);
		} catch (Exception e) {
			LOG.error("SmartPDFService - exception occurred sending HttpServletResponse: " + e.getMessage());
		}

	}

	private static String buildPDFName(String clientId, String formType, String taxYear) {
		return clientId + "_" + formType + "-" + taxYear + ".pdf";
	}

	private void pdfService(HttpServletRequest request, HttpServletResponse response) {
		LOG.info("SmartPDFService - PDFService request");

		JSONObject awdProp = smartPDFAWDUtil.getAWDConnectionProp(request.getParameter("envName"),
				request.getParameter("sessionId"));
		String awdBusArea = awdProp.get("businessArea").toString();
		String awdUser = awdProp.get("awdUserId").toString();

		String awdObjId = smartPDFAWDUtil.createAWDObj(request);

		String awdSourceId = null;
		if (awdObjId != null) {
			awdSourceId = smartPDFAWDUtil.createAWDSource(request, awdObjId);
		}

		String responseXml;
		if (awdObjId != null && awdSourceId != null) {
			responseXml = "<awdObj>" + "<busArea>" + awdBusArea + "</busArea>" + " <user>" + awdUser + "</user>"
					+ "<objId>" + awdObjId + "</objId>" + "</awdObj>";
		} else {
			responseXml = "<error>Failed to create work object</error>";
		}

		try {
			response.setContentType("text/xml");
			response.getWriter().write(responseXml);
		} catch (IOException e) {
			LOG.error(e.getMessage(), e);
		}
	}

	/************* public methods *****************/

	@Override
	public void service(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
		request.setCharacterEncoding("UTF-8");

		String service = request.getParameter("service");

		if ("generate".equals(service)) {
			generatePDFService(request, response);
		} else if ("fax".equals(service) || "email".equals(service)) {
			pdfService(request, response);
		}
	}

	/************* Return parameters to SmartPDF *****************/

	public String getFormType() {
		return formType;
	}

	public String getDecimalDelimitor() {
		if ("fr".equals(locale)) {
			return decimalDelimitorFr;
		} else {
			return decimalDelimitorEn;
		}
	}

	public String getCulture() {
		return locale;
	}

	public String getConfigurationPath() {
		String clientPath = dataPath + "/" + clientId + "/" + configDirectory;
		String commonPath = dataPath + "/" + commonDirectory + "/" + configDirectory;
		String path;

		File configFile = new File(clientPath + "/" + formType + ".xml");
		if (configFile.exists()) {
			path = clientPath;
		} else {
			path = commonPath;
		}

		return path;
	}

	public String getResourcesPath() {
		String clientPath = dataPath + "/" + clientId + "/" + resourcesDirectory;
		String commonPath = dataPath + "/" + commonDirectory + "/" + resourcesDirectory;
		String path;

		File resourceFile = new File(clientPath + "/" + formType + "_" + locale + ".xml");
		if (resourceFile.exists()) {
			path = clientPath;
		} else {
			path = commonPath;
		}

		return path;
	}

	public String getImagePath() {
		String clientPath = dataPath + "/" + clientId + "/" + imageDirectory;
		String commonPath = dataPath + "/" + commonDirectory + "/" + imageDirectory;
		String path;

		File imageFile = new File(clientPath + "/" + formType + "_page.jpg");
		if (imageFile.exists()) {
			path = clientPath;
		} else {
			path = commonPath;
		}

		return path;
	}
}