let str = ReasonReact.string;

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

let timerEffect = (dispatch) =>
  WonkaJs.interval(1000)
    |> Wonka.forEach((._) => dispatch(Tick))
    |> _ => None;
    
[@react.component]
let make = () => {
  let ({ timer }, dispatch) = React.useReducer(reducer, { timer: 0, running: false })

  React.useEffect1(() => timerEffect(dispatch), [||]);
    
  <div>
    <button onClick={_event => dispatch(Start)}>
      {"Start" |> str}
    </button>
    <button onClick={_event => dispatch(Stop)}>
      {"Stop" |> str}
    </button>
    <button onClick={_event => dispatch(Reset)}>
      {"Reset" |> str}
    </button>

    <span className=TimerStyles.timer>{"Time: " ++ string_of_int(timer) |> str}</span>
  </div>
};
