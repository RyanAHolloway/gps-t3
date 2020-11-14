pipeline {
     agent any

      options {
           buildDiscarder(logRotator(numToKeepStr: '10'))
      }

      stages {
           stage('Build') {
                steps {
                     sh 'make -f Makefile2'
                }
           }
           stage('Run') {
           		steps {
           			sh 'cd bin && ./gpx-tests --log_level=success --run_test=maxLatitude'
           		}
           } 
     }
}
