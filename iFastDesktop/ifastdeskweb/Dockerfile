FROM openjdk:8-jdk-alpine
COPY ./ifastdeskweb_mqconfig.properties /etc
VOLUME /tmp
ARG JAR_FILE
ADD ${JAR_FILE} app.jar
ENTRYPOINT ["java","-Djava.security.egd=file:/dev/./urandom","-Dconfig.path=/ifds/ifastdeskweb_mqconfig.properties",  "-jar","/app.jar"]



