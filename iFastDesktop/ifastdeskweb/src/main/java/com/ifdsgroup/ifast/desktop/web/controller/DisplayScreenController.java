package com.ifdsgroup.ifast.desktop.web.controller;

import java.util.Enumeration;

import javax.servlet.http.HttpServletRequest;

import org.apache.logging.log4j.LogManager;
import org.apache.logging.log4j.Logger;
import org.springframework.stereotype.Controller;
import org.springframework.ui.Model;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RequestMethod;
import org.springframework.web.servlet.ModelAndView;

import com.ifdsgroup.ifast.desktop.web.xpath.util.CommonUtil;

/**
 * This class is the landing controller for all the requests having jobname as
 * 'DisplayScreen'. It is a Spring MVC controller
 * 
 * @author if993762
 *
 */

@Controller
public class DisplayScreenController {

	/*
	 * Logger to log any errors/issues on the log file
	 */
	private static final Logger LOG = LogManager.getLogger(DisplayScreenController.class);

	/**
	 * This method endpoint returns the view (DesktopMain html page) in response
	 * 
	 * @param servletRequest
	 * @param model
	 * @return
	 */
	@RequestMapping(value = "/displayScreen", method = { RequestMethod.POST, RequestMethod.GET })
	public ModelAndView doDisplayScreen(HttpServletRequest servletRequest, Model model) {

		LOG.debug("DisplayScreenController : Request Header : "+ CommonUtil.getHeaderInfo(servletRequest));

		ModelAndView m = new ModelAndView();

		model.addAttribute("request", servletRequest.getParameterMap());

		m.setViewName("DesktopWeb.Main");

		return m;

	}
}