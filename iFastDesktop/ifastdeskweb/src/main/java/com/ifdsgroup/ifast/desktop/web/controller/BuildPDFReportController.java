package com.ifdsgroup.ifast.desktop.web.controller;

import java.io.ByteArrayOutputStream;
import java.io.File;
import java.io.IOException;
import java.io.StringReader;
import java.util.Properties;

import javax.servlet.http.HttpServletResponse;
import javax.xml.transform.Result;
import javax.xml.transform.Source;
import javax.xml.transform.Transformer;
import javax.xml.transform.TransformerException;
import javax.xml.transform.TransformerFactory;
import javax.xml.transform.sax.SAXResult;
import javax.xml.transform.stream.StreamResult;
import javax.xml.transform.stream.StreamSource;

import org.apache.fop.apps.FOUserAgent;
import org.apache.fop.apps.Fop;
import org.apache.fop.apps.FopFactory;
import org.apache.fop.apps.MimeConstants;
import org.apache.logging.log4j.LogManager;
import org.apache.logging.log4j.Logger;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.core.io.ResourceLoader;
import org.springframework.http.MediaType;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RequestMethod;
import org.springframework.web.bind.annotation.RequestParam;
import org.springframework.web.bind.annotation.RestController;
import org.xml.sax.SAXException;

import com.ifdsgroup.ifast.desktop.web.core.config.ServicesConfiguration;
import com.ifdsgroup.ifast.desktop.web.service.SmartViewCallService;

@RestController
public class BuildPDFReportController {

	/*
	 * Logger to log any errors/issues in the log file
	 */
	private static final Logger LOG = LogManager.getLogger(BuildPDFReportController.class);

	/*
	 * Reference to SmartViewCallService
	 */
	private final SmartViewCallService smartViewCallService;

	@Autowired
	private ResourceLoader resourceLoader;

	@Autowired
	private ServicesConfiguration servicesConfig;

	/*
	 * Constructor used to inject dependencies
	 */
	public BuildPDFReportController(SmartViewCallService smartViewCallService) {
		this.smartViewCallService = smartViewCallService;
	}

	@RequestMapping(value = "/buildPDFReport", method = RequestMethod.POST, produces = MediaType.APPLICATION_PDF_VALUE, consumes = MediaType.APPLICATION_FORM_URLENCODED_VALUE)
	public byte[] processRequest(@RequestParam String template, @RequestParam String report,
			@RequestParam(value = "BuildPDFReport-data") String body, HttpServletResponse response)
			throws TransformerException, IOException, SAXException {
		LOG.debug("***We are in buildpdf report***");
		LOG.debug("Template: " + template);
		LOG.debug("Report: " + report);
		LOG.debug("Body: " + body);

		// Get the data for the pdf using smartView
		String data = smartViewCallService.process("<request>" + body + "</request>", null).getData();

		ClassLoader classLoader = getClass().getClassLoader();

		TransformerFactory factory = TransformerFactory.newInstance();

		// ************Compile the xml response from smartView into the
		// template.xsl file **********
		Source xmlSource = new StreamSource(new StringReader(data));

		// Changed to support stream from jar
		// Source xslSource = new StreamSource(new
		// File(classLoader.getResource("fop/" + template + ".xsl").getFile()));
		Source xslSource = new StreamSource(
				resourceLoader.getResource("classpath:fop/" + template + ".xsl").getInputStream());

		ByteArrayOutputStream foStream = new ByteArrayOutputStream();
		StreamResult xhtmlResult = new StreamResult(foStream);

		Transformer xml2xhtmlTransformer = factory.newTransformer(xslSource);

		// Write the compiled xhtml result to xhtmlResult
		xml2xhtmlTransformer.transform(xmlSource, xhtmlResult);
		// *******************End of xml compilation**********************

		// *********Compile the xhtml into the XSL:FO and then into the
		// pdf****************
		// The XSL:FO template

		// Changed to support stream from jar
		// File xhtml2fo = new
		// File(classLoader.getResource("fop/xhtml2fo.xsl").getFile());
		// File xhtml2fo = new
		// File(resourceLoader.getResource("classpath:fop/xhtml2fo.xsl").getFile());

		// create an instance of fop factory
		Properties props = servicesConfig.getProperties();
		FopFactory fopFactory = FopFactory
				.newInstance(new File(props.getProperty("pdf.conf.file") + "/" + "config.xconf"));

		FOUserAgent agent = fopFactory.newFOUserAgent();

		ByteArrayOutputStream pdfByteArray = new ByteArrayOutputStream();
		try {
			// Construct fop with desired output format
			Fop fop = fopFactory.newFop(MimeConstants.MIME_PDF, agent, pdfByteArray);

			// // Setup XSLT
			Transformer xhtml2PDFTranformer = factory.newTransformer(
					new StreamSource(resourceLoader.getResource("classpath:fop/xhtml2fo.xsl").getInputStream()));

			// Resulting SAX events (the generated FO) must be piped through to
			// FOP
			Result res = new SAXResult(fop.getDefaultHandler());

			// Start XSLT transformation and FOP processing
			// That's where the XML is first transformed to XSL-FO and then
			// PDF is created
			ByteArrayOutputStream b = (ByteArrayOutputStream) xhtmlResult.getOutputStream();
			System.out.println(foStream.toString());
			xhtml2PDFTranformer.transform(new StreamSource(new StringReader(b.toString())), res);
		} catch (Exception e) {
			LOG.debug(e.getMessage(), e);
		}

		// Set the header so the application knows to download this file
		response.setHeader("Content-Disposition", "attachment; filename=\"" + report + ".pdf\"");

		//
		// Driver localDriver = new Driver();
		// localDriver.setRenderer(1);
		// localDriver.setOutputStream(pdfByteArray);
		// SAXResult localSAXResult = new
		// SAXResult(localDriver.getContentHandler());
		//
		// ByteArrayOutputStream localByteArrayOutputStream2 = new
		// ByteArrayOutputStream();
		// StreamSource localStreamSource = new StreamSource(new
		// ByteArrayInputStream(localByteArrayOutputStream2.toByteArray()));
		//
		// xhtml2PDFTranformer.transform(localStreamSource, localSAXResult);
		//
		
		if(pdfByteArray != null){
			LOG.debug("BuildPDFReportController : pdfByteArray size is : "+pdfByteArray.size());
		}
		
		// Return the pdf as an array of bytes
		return pdfByteArray.toByteArray();
	}
}
