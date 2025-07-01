import { signOut } from "../../reducers/sign";
import LoadingSpinner from "../LoadingSpinner";
import { useEffect } from "react";
import { useDispatch } from "react-redux";
import { useNavigate } from "react-router-dom";


const SignOut = () => {
    const dispatch = useDispatch();
    const navigate = useNavigate();

    useEffect(() => {
        dispatch(signOut());
        navigate("/", { replace: true });

    }, [dispatch, navigate]);

    return <LoadingSpinner />;
};

export default SignOut;
