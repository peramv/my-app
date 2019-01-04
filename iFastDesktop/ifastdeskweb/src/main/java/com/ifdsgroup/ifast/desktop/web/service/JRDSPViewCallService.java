package com.ifdsgroup.ifast.desktop.web.service;

import static com.ifdsgroup.ifast.desktop.web.core.config.DesktopWebConstants.SESSION_ID;
import static com.ifdsgroup.ifast.desktop.web.core.config.DesktopWebConstants.SLOT_NAME;
import static com.ifdsgroup.ifast.desktop.web.xpath.util.XPathUtil.buildDocument;
import static com.ifdsgroup.ifast.desktop.web.xpath.util.XPathUtil.buildXPath;
import static com.ifdsgroup.ifast.desktop.web.xpath.util.XPathUtil.compile;
import static com.ifdsgroup.ifast.desktop.web.xpath.util.XPathUtil.evaluateXPath;

import javax.xml.xpath.XPath;
import javax.xml.xpath.XPathConstants;
import javax.xml.xpath.XPathExpression;

import org.apache.http.client.methods.CloseableHttpResponse;
import org.apache.http.client.methods.HttpGet;
import org.apache.http.client.methods.HttpPost;
import org.apache.http.entity.StringEntity;
import org.apache.http.impl.client.CloseableHttpClient;
import org.apache.http.impl.client.HttpClients;
import org.apache.http.util.EntityUtils;
import org.apache.logging.log4j.LogManager;
import org.apache.logging.log4j.Logger;
import org.dom4j.DocumentHelper;
import org.springframework.beans.factory.annotation.Value;
import org.springframework.stereotype.Service;
import org.thymeleaf.util.StringUtils;
import org.w3c.dom.Document;
import org.w3c.dom.Element;
import org.w3c.dom.Node;

import com.ifdsgroup.ifast.desktop.web.dto.SmartViewPayload;
import com.ifdsgroup.ifast.desktop.web.xpath.util.XPathUtil;

/**
 * 
 * This class is a business layer for SmartViewController to execute business
 * logic. It invokes the calls to backend API's.
 * 
 * @author if993762
 *
 */
@Service
public class JRDSPViewCallService {
	
	
	@Value("${jrdsp.services.url}")
	private String jrdspServiceURL;
	

    /*
     * Enum that represents type of service supported by the back-end API's
     */
    enum SrvcType {
        AUTH, INQUIRY
    }

    /*
     * Logger to log any errors/issues in the log file
     */
    private static final Logger LOG = LogManager.getLogger(JRDSPViewCallService.class);

    /*
     * Reference to back-end API invoker
     */
    private final IFastApiInvoker apiInvoker;

    /*
     * Constructor used to inject dependencies
     */
    public JRDSPViewCallService(IFastApiInvoker apiInvoker) {
        this.apiInvoker = apiInvoker;
    }
    
    
    /**
     * Business method that executes XPath expressions in order to extract data
     * from XML request payload and pass necessary parameters to call back-end
     * API through Sonic Messenger.
     * 
     * @param xml
     * @return PayLoad object
     */
    public SmartViewPayload process(String xml, String ignoreErrorCode) {

       /* Document document = XPathUtil.buildDocument(xml);
        XPath xp = XPathUtil.buildXPath();

        
         * XPath expressions are used to extract necessary data from XML request
         * Payload
         
        String root = XPathUtil.evaluateXPath(xp, "name(/*)", document.getDocumentElement());
        String apiNameHeader = XPathUtil.evaluateXPath(xp, "name(/" + root + "/*)", document.getDocumentElement());
        String apiRequestHeader = XPathUtil.evaluateXPath(xp, "name(/" + root + "/" + apiNameHeader + "/*)",
                document.getDocumentElement());
        String sessionId = XPathUtil.evaluateXPath(xp,
                "//" + root + "/" + apiNameHeader + "/" + apiRequestHeader + "/" + SESSION_ID + "/text()",
                document.getDocumentElement());
        String slotName = XPathUtil.evaluateXPath(xp,
                "//" + root + "/" + apiNameHeader + "/" + apiRequestHeader + "/" + SLOT_NAME + "/text()",
                document.getDocumentElement());

        
         * Method reference call to sonic implementation class with extracted
         * parameters (from XML request payload).
         
        return IFastApiInvoker.handlingChecked(apiInvoker::apply, xml, sessionId, slotName, ignoreErrorCode);*/
    	
    	
    	//Make Calls to JRDSP 
    	// 1. Convert the request XML to JSON
    	// 2. Make the REST call with the JSON
    	// 3. Convert the response JSON to XML
    	// 4. Return the XML

    	
    	// 1. Convert the request XML to JSON
    	
    	String jsonPayload=convertPayloadToJson(xml);
    	
    	System.out.println("jsonPayload : "+jsonPayload);
    	
    	// 2. Make the REST call with the JSON
    	
    	CloseableHttpClient httpClient = HttpClients.createDefault();
		HttpGet httpGet = new HttpGet(jrdspServiceURL + "/hello");
		/*httpPost.addHeader("Content-Type", "application/vnd.dsttechnologies.awd+xml");
		httpPost.addHeader("REMOTE_USER", awdUser);
		httpPost.addHeader("B2BSignature", getB2BSignature(awdProp));*/
		String requestXml = "";
		//LOG.info("SmartPDFAWDUtil - CreateObj AWD API requestXml:\n" + requestXml);

		String responseJson = null;
		try {
			//httpGet.setEntity(new StringEntity(requestXml));
			CloseableHttpResponse httpResponse = httpClient.execute(httpGet);
			responseJson = EntityUtils.toString(httpResponse.getEntity());
			//LOG.info("SmartPDFAWDUtil - CreateObj AWD API responseXml:\n " + responseXml);
		} catch (Exception e) {
			e.printStackTrace();
			LOG.error(e.getMessage(), e);
		}

		System.out.println("responseJson : "+responseJson);
	
    	return null;
    }
    
    
    private String convertPayloadToJson(String xml) {
		// TODO Auto-generated method stub
    	
    	if(StringUtils.isEmpty(xml))
    	{
    		return "{}";
    	}
    	else
    	{
    		return "{\"accountNumber\":123,\"accountName\":\"RDSP Account 1\"}";
    	}
	}

	public static Node getErrorsNode(String sonicResponse) {

        String expression = "//RequestStatus/Errors";

        Document document = buildDocument(sonicResponse);
        XPath xp = buildXPath();
        XPathExpression xpath = compile(xp, expression);

        return (Node) evaluateXPath(xpath, document, XPathConstants.NODE);
    }
    
    public static String getErrorCode(String errors) {
        Document document = buildDocument(errors);
        Element documentElement = document.getDocumentElement();
        XPath xp = buildXPath();

        return evaluateXPath(xp, "//Error/errorCode/text()", documentElement);
    }

    public static String getSonicResponseStatus(String sonicResponse) {

        Document document = buildDocument(sonicResponse);
        Element documentElement = document.getDocumentElement();
        XPath xp = buildXPath();

        return evaluateXPath(xp, "//RequestStatus/status/text()", documentElement);
    }

}