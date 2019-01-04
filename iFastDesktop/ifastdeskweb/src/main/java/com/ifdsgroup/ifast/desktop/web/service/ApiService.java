package com.ifdsgroup.ifast.desktop.web.service;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

@Service
public class ApiService {

    @Autowired
    protected ApiDelegate apiDelegate;
    
    @SuppressWarnings("unchecked")
    public <T> T inquireApi(Object request, Class<T> responseClass) {
        return (T)apiDelegate.callApi(request);
    }
}
