import "./App.css";
import TypeIt from "typeit-react";

const typeStyle = {
  fontSize: "40px",
  fontFamily: "Roboto Mono",
};

function App() {
  return (
    <>
      <div></div>
      <TypeIt
        style={typeStyle}
        element={"h1"}
        getBeforeInit={(instance) => {
          instance
            .type("The STAB Programming Language.")
            .pause(750)
            .move(-22)
            .delete(1)
            .type("b")
            .pause(540)
            .move(-2)
            .delete(1)
            .type("t");

          // Remember to return it!
          return instance;
        }}
      />
      <div className="card">
        <button>
          <a href="https://github.com/Abhilekhgautam/StAb/releases">
            Download v0.1.0
          </a>
        </button>
        <p>
          Create a new file <code>test.st</code> and start coding.
        </p>
      </div>

      <p className="read-the-docs">
        Don&apos;t know where to start? Look at some{" "}
        <a href="https://github.com/Abhilekhgautam/StAb/tree/main/examples">
          Examples
        </a>
      </p>
      <p className="read-the-docs">
        Learn more about the language
        <a href="https://github.com/Abhilekhgautam/StAb"> here</a>.
      </p>
    </>
  );
}

export default App;
