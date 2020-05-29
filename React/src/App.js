import React, { useState } from 'react';
import Life from './Life.js';
// import logo from './logo.svg';
// import './App.css';

function App() {
  // return (
  //   <div className="App">
  //     <header className="App-header">
  //       <img src={logo} className="App-logo" alt="logo" />
  //       <p>
  //         Edit <code>src/App.js</code> and save to reload.
  //       </p>
  //       <a
  //         className="App-link"
  //         href="https://reactjs.org"
  //         target="_blank"
  //         rel="noopener noreferrer"
  //       >
  //         Learn React
  //       </a>
  //     </header>
  //   </div>
  // );

  const [content, setContent] = useState("");

  function getFile() {
    if (window.File && window.FileReader && window.FileList && window.Blob) {
      var file = document.querySelector('input[type=file]').files[0];
      var reader = new FileReader();
      var textFile = /text.*/;

      if (file.type.match(textFile)) {
        reader.onload = function (event) {
          Life({input: event.target.result, setContent});
        }
      } else {
        setContent("It doesn't seem to be a text file!");
      }
      reader.readAsText(file);
    } else {
      alert("Your browser is too old to support HTML5 File API");
    }
  }

  return (
    <>
      <input type="file" onChange={getFile} /><br/><br/>
      <span style={{whiteSpace: "pre-wrap"}}>{content}</span>
    </>
  );
}

export default App;
