pipeline {
  agent any

  environment {
    IMAGE = "cpp-crow-dashboard:latest"
  }

  stages {
    stage('Checkout') {
      steps {
        git url: 'https://github.com/kunjbhuva7/cpp-crow-dashboard.git', branch: 'main'
      }
    }

    stage('Build with CMake') {
      steps {
        sh '''
          rm -rf build
          cmake -S . -B build
          cmake --build build -j$(nproc)
        '''
      }
    }

    stage('Build Docker Image') {
      steps {
        sh 'docker build -t ${IMAGE} .'
      }
    }

    stage('Run Locally') {
      steps {
        sh '''
          docker stop crow_dashboard || true
          docker rm crow_dashboard || true
          docker run -d --name crow_dashboard -p 9999:9999 ${IMAGE}
        '''
      }
    }
  }

  post {
    success {
      echo "✅ Dashboard running at: http://localhost:9999"
    }
    failure {
      echo "❌ Pipeline failed. Check logs."
    }
  }
}

