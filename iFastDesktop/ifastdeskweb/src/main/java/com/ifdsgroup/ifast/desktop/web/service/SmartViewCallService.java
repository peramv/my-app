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

import org.apache.logging.log4j.LogManager;
import org.apache.logging.log4j.Logger;
import org.springframework.stereotype.Service;
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
public class SmartViewCallService {

    /*
     * Enum that represents type of service supported by the back-end API's
     */
    enum SrvcType {
        AUTH, INQUIRY
    }

    /*
     * Logger to log any errors/issues in the log file
     */
    private static final Logger LOG = LogManager.getLogger(SmartViewCallService.class);

    /*
     * Reference to back-end API invoker
     */
    private final IFastApiInvoker apiInvoker;

    /*
     * Constructor used to inject dependencies
     */
    public SmartViewCallService(IFastApiInvoker apiInvoker) {
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

        Document document = XPathUtil.buildDocument(xml);
        XPath xp = XPathUtil.buildXPath();

        /*
         * XPath expressions are used to extract necessary data from XML request
         * Payload
         */
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

        /*
         * Method reference call to sonic implementation class with extracted
         * parameters (from XML request payload).
         */
        return IFastApiInvoker.handlingChecked(apiInvoker::apply, xml, sessionId, slotName, ignoreErrorCode);

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