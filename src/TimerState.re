/* State declaration */
type state = {
  running: bool,
  timer: int,
};

/* Action declaration */
type action =
  | Start
  | Stop
  | Reset
  | Tick

let reducer = (state, action) =>
  switch (action) {
    | Start => {...state, running: true}
    | Stop => {...state, running: false}
    | Reset => {...state, timer: 0}
    | Tick => 
      switch (state.running) {
        | true => {...state, timer: state.timer + 1}
        | _ => state
      }      
  };

type timerState = {
  state: state,
  dispatch: action => unit
};

let timerContext = React.createContext();
let useTimer = () => 
  React.useContext(timerContext);


[@react.component]
let timerProvider = (~children) => {
  let (state, dispatch) = React.useReducer(reducer, { timer: 0, running: false });
  let value = {
    state: state,
    dispatch: dispatch
  };
  
  React.createElement(
    React.Context.provider(timerContext)
  )
};