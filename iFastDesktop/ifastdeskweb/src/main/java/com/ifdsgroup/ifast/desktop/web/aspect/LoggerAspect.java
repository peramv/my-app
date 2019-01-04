package com.ifdsgroup.ifast.desktop.web.aspect;

import javax.servlet.http.HttpServletRequest;

import org.apache.logging.log4j.LogManager;
import org.apache.logging.log4j.Logger;
import org.aspectj.lang.annotation.After;
import org.aspectj.lang.annotation.Aspect;
import org.aspectj.lang.annotation.Before;
import org.aspectj.lang.annotation.Pointcut;
import org.springframework.stereotype.Component;

/**
 * This class is an Aspect Class that applies AOP to perform cross cutting
 * logging throughout the application
 * 
 * @author if993925
 *
 */
@Aspect
@Component
public class LoggerAspect {

	/*---- Pointcuts -----*/

	private static final Logger LOG = LogManager.getLogger(LoggerAspect.class);

	// execution of displayScreen method
	@Pointcut("execution(* com.ifdsgroup.ifast.desktop.web.controller.DisplayScreenController.doDisplayScreen (javax.servlet.http.HttpServletRequest, org.springframework.ui.Model))")
	public void DisplayScreenPointcut() {
	}

	// execution of any processRequest method
	@Pointcut("execution(* com.ifdsgroup.ifast.desktop.web.controller.*.processRequest (javax.servlet.http.HttpServletRequest, java.lang.String))")
	public void ProcessRequestPointcut() {
	}

	// execution of a method in RetrieveCacheController
	@Pointcut("execution(* com.ifdsgroup.ifast.desktop.web.controller.RetrieveCacheController.* (..))")
	public void RetrieveCacheControllerPointcut() {
	}

	// execution of a method in SmartViewController
	@Pointcut("execution(* com.ifdsgroup.ifast.desktop.web.controller.SmartViewController.* (..))")
	public void SmartViewControllerPointcut() {
	}

	// execution of a method in UpdateCacheController
	@Pointcut("execution(* com.ifdsgroup.ifast.desktop.web.controller.UpdateCacheController.* (..))")
	public void UpdateCacheControllerPointcut() {
	}

	// execution of processUpdateCache in Cache Service
	@Pointcut("execution(* com.ifdsgroup.ifast.desktop.web.service.CacheService.processUpdateCache (*))")
	public void processUpdateCachePointcut() {
	}

	// execution of processRetrieveCache in Cache Service
	@Pointcut("execution(* com.ifdsgroup.ifast.desktop.web.service.CacheService.processRetrieveCache (*))")
	public void processRetrieveCachePointcut() {
	}

	// execution of any method in SmartViewCallService
	@Pointcut("execution(* com.ifdsgroup.ifast.desktop.web.service.SmartViewCallService.* (..))")
	public void SmartViewCallServicePointcut() {
	}

	/* ---- Before Advice ---- */
	@Before("DisplayScreenPointcut()")
	public void beforedoDisplayScreenAdvice() {
		LOG.debug("DisplayingScreenController called");
	}

	@Before("RetrieveCacheControllerPointcut()")
	public void beforeRetrieveCacheControllerAdvice() {
		LOG.debug("RetrieveCacheController called");
	}

	@Before("SmartViewControllerPointcut()")
	public void beforedoSmartViewControllerAdvice() {
		LOG.debug("SmartViewController called");
	}

	@Before("UpdateCacheControllerPointcut()")
	public void beforeUpdateCacheControllerAdvice() {
		LOG.debug("UpdateCacheController called");
	}

	@Before("ProcessRequestPointcut() && args(request,payload,..)")
	public void beforeProcessRequestAdvice(HttpServletRequest request, String payload) {
		LOG.debug("Processing Request with the following payload:");
		LOG.debug("Request payload: " + payload);
	}

	@Before("SmartViewCallServicePointcut()")
	public void beforeSmartViewCallServiceAdvice() {
		LOG.debug("In SmartViewCallService");
	}

	@Before("processUpdateCachePointcut()")
	public void beforeUpdateCacheAdvice() {
		LOG.debug("In Update Cache");
	}

	@Before("processRetrieveCachePointcut()")
	public void beforeRetrieveCacheAdvice() {
		LOG.debug("In Retrieve Cache");
	}

	/* ---- After Advice ---- */
	@After("DisplayScreenPointcut()")
	public void afterdoDisplayScreenAdvice() {
		LOG.debug("DisplayScreenController has successfully completed");
	}

	@After("RetrieveCacheControllerPointcut()")
	public void afterRetrieveCacheControllerAdvice() {
		LOG.debug("RetrieveCacheController has successfully completed");
	}

	@After("SmartViewControllerPointcut()")
	public void afterdoSmartViewControllerAdvice() {
		LOG.debug("SmartViewController has successfully completed");
	}

	@After("UpdateCacheControllerPointcut()")
	public void afterUpdateCacheControllerAdvice() {
		LOG.debug("UpdateCacheController has successfully completed");
	}

	@After("ProcessRequestPointcut()")
	public void afterProcessRequestAdvice() {
		LOG.debug("Request successfully processed");
	}

	@After("processUpdateCachePointcut()")
	public void afterUpdateCacheAdvice() {
		LOG.debug("Leaving Update Cache");
	}

	@After("processRetrieveCachePointcut()")
	public void afterRetrieveCacheAdvice() {
		LOG.debug("Leaving Retrieve Cache");
	}

	@After("SmartViewCallServicePointcut()")
	public void afterSmartViewCallServiceAdvice() {
		LOG.debug("Leaving SmartViewCallService");
	}

}
