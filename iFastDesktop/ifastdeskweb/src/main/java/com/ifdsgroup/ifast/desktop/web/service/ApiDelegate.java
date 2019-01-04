package com.ifdsgroup.ifast.desktop.web.service;


import java.io.IOException;
import java.io.StringReader;

import javax.xml.parsers.DocumentBuilder;
import javax.xml.parsers.DocumentBuilderFactory;
import javax.xml.parsers.ParserConfigurationException;
import javax.xml.transform.Source;
import javax.xml.transform.TransformerException;
import javax.xml.transform.TransformerFactory;
import javax.xml.transform.dom.DOMResult;
import javax.xml.transform.dom.DOMSource;
import javax.xml.transform.stream.StreamSource;

import org.apache.log4j.Logger;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.oxm.Marshaller;
import org.springframework.oxm.Unmarshaller;
import org.springframework.oxm.XmlMappingException;
import org.springframework.stereotype.Component;
import org.w3c.dom.Document;

import com.ifdsgroup.integration.util.XMLUtil;
import com.ifdsgroup.msg.client.appmsg.auth.AuthException;

/**
 * All API invocations are delegated to the callApi method of this class.
 */
@Component
public class ApiDelegate {

    private static Logger logger = Logger.getLogger(ApiDelegate.class);

    @Autowired
    private Marshaller marshaller;

    @Autowired
    private Unmarshaller unmarshaller;
    
    /*
     * Reference to back-end API invoker
     */
    private final IFastApiInvoker apiInvoker;
    
    /*
     * Constructor used to inject dependencies
     */
    public ApiDelegate(IFastApiInvoker apiInvoker) {
        this.apiInvoker = apiInvoker;
    }

   /**
    *  Sends the request to API and returns the response
    * @param request
    * @return response
    */
    public Object callApi(Object request) {

        DOMResult domResult = new DOMResult();
        Document doc = null;
        Object response = null;
		try {

            DocumentBuilderFactory dbf = DocumentBuilderFactory.newInstance();
            dbf.setNamespaceAware(true);
            DocumentBuilder db = null;

            db = dbf.newDocumentBuilder();
            doc = db.newDocument();
            marshaller.marshal(request, domResult);
            doc = (Document) domResult.getNode();
            String reqStr = XMLUtil.serializePretty(doc);
            logger.info("Request: " + reqStr);
            //Document result = IFastMsgSingleton.INSTANCE.call(clientCode, properties.apiTransactionType, doc);
            Document result = loadXMLFrom(apiInvoker.apply(reqStr, null, null));

            if (logger.isDebugEnabled()) {
                String respStr = XMLUtil.serializePretty(result);
                logger.debug("Response: " + respStr);
            }

            response = unmarshaller.unmarshal(new DOMSource(result));
		} catch (Exception e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} 
        logger.info("API Response received. Response: " + response);

        return response;
    }
    
    private Document loadXMLFrom(String xml) throws TransformerException {
        Source source = new StreamSource(new StringReader(xml));
        DOMResult result = new DOMResult();
        TransformerFactory.newInstance().newTransformer().transform(source , result);
        return (Document) result.getNode();
    } 
}
